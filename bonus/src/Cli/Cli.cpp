//
// Author: Marwane Khsime 
// Date: 2017-02-20 02:22:21 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-20 02:22:21
//

#include "Cli.hpp"

Cli::Cli(const Parser &parser) {

  this->regParse = parser.regParse;
  this->circuit = parser.getCircuit();
  this->outputs = parser.getOutputs();
  this->clocks = parser.getClocks();
  this->looping = false;

  this->func["exit"] = std::bind(&Cli::Exit, this);
  this->func["display"] = std::bind(&Cli::Display, this);
  this->func["simulate"] = std::bind(&Cli::Simulate, this);
  this->func["loop"] = std::bind(&Cli::Loop, this);
  this->func["dump"] = std::bind(&Cli::Dump, this);
  this->func["help"] = std::bind(&Cli::Help, this);
  this->func["clear"] = std::bind(&Cli::Clear, this);

  if (this->circuit.size() == 0 || this->outputs.size() == 0)
    throw Error("CLI cannot be setted because the circuit is empty or there is no output.\n");
}

Cli::~Cli() {}

void    Cli::init()
{
  // To store the command lines.
  std::string cmd;

  // Launch a first Simulation with a Display.
  Simulate();
  Display();

  //   std::cout << "=== NANOTEKSPICE CLI ===" << std::endl << std::endl;
  std::cout << "> ";

  // Get Commands Lines.
  while (getline(std::cin, cmd)) {

      cmd = EpurString(cmd);
      // If the command is known by 'func' map, execute it.
      if (this->func.find(cmd) != this->func.end())
        this->func[cmd]();
      
      // If it's a Load
      else if (cmd.substr(0, cmd.find(' ')) == "load") {
          Load(cmd.substr(cmd.find(" ") + 1));
      }

      // If it's a SetInput
      else if (this->regParse->exec(cmd.c_str(), this->regParse->cli_value))
          SetInput();

      // The commandline is empty, or invalid.
      else {
          if (!(!cmd.size()))
            std::cout << "nanotekspice : command not found: " << cmd << std::endl;
        }
      std::cout << "> ";
    }
  // Exit the Cli.
//  std::cout << "exit" << std::endl;
}

void    Cli::Exit() {
  // Exit the program
  exit(EXIT_SUCCESS);
}

void    Cli::Display() {
  // Call the dump method of each output.
  std::map<std::string, AComponent *>::iterator it;

  for (it = outputs.begin(); it != outputs.end(); it++) {
      it->second->Dump();
    }
}

void    Cli::SetInput() {
  std::pair<std::string, int> tmp = this->regParse->getInpValue();

  // Check if the component exist.
  if (this->circuit.find(tmp.first) != this->circuit.end()) {
      // Check if the component selected is an input.
      if (this->circuit[tmp.first]->getType() == "input")
        // If it is, set the state of the input.
        this->circuit[tmp.first]->setStateAtPin(1, (nts::Tristate)tmp.second);
      else // else, print an error (only inputs can be setted by cli).
        std::cout << "nanotekspice : " << tmp.first << " is not an input." << std::endl;
    } else  // If the component doesn't exist.
    std::cout << "nanotekspice: " << tmp.first << " doesn't exist." << std::endl;
}

void    Cli::Simulate() {

  for (std::map<std::string, AComponent *>::iterator it = this->circuit.begin(); it != this->circuit.end(); it++) {
      if (it->second->getType() != "output")
        it->second->computeGates();
    }

  for (std::map<std::string, AComponent *>::iterator it = this->outputs.begin(); it != this->outputs.end(); it++) {
      it->second->computeGates();
    }

  for (std::vector<AComponent *>::iterator it = this->clocks.begin(); it != this->clocks.end(); it++) {
      (*it)->setStateAtPin(1, (nts::Tristate)!(*it)->getStateAtPin(1));
    }
}

// For the Loop, to know if we continue the looping or if we break.
static bool isLooping = false;

// For Loop(), on SIGINT, change the value of the variable isLooping
// to break the loop.
void    Cli::signalHandler(int signum) {
  isLooping = false;
  (void)signum;
}

void    Cli::Loop() {
  // Create and set the sigaction handler.
  struct  sigaction   sigintHandler;

  sigintHandler.sa_handler = Cli::signalHandler;
  sigemptyset(&sigintHandler.sa_mask);
  sigintHandler.sa_flags = 0;
  sigaction(SIGINT, &sigintHandler, NULL);
  isLooping = true;

  // Loop the Simulate function until SIGINT.
  while (isLooping)
    Simulate();

  // Clear the Handler.
  sigintHandler.sa_handler = NULL;
}

void    Cli::Dump() {
  // Call the Dump method of each component of the circuit.
  std::map<std::string, AComponent *>::iterator it;

  std::cout << "\n=== DUMP ===\n" << std::endl;
  for (it = this->circuit.begin(); it != this->circuit.end(); it++)
    {
      it->second->Dump();
      std::cout << std::endl;
    }
}

void    Cli::Help() {
  // Print the helper.

  std::cout <<
            "Usage:     ./nanotekspice [FILE] [INPUTS]" << std::endl << std::endl
            << "| CLI COMMANDS :" << std::endl
            << "|__ load [PATH] [ARGS]\t\tload a config." << std::endl
            << "|__ display\t\tprints on stdout the value of all outputs sorted by name." << std::endl
            << "|__ simulate\t\tlaunches a simulation." << std::endl
            << "|__ loop\t\tlaunches simulations without prompting again until SIGINT." << std::endl
            << "|__ dump\t\tcall the Dump method of every component." << std::endl
            << "|__ [INPUT]=[VALUE]\tchanges the value of an input. (Not a clock)" << std::endl
            << "|__ exit\t\tcloses the program." << std::endl
            << "|__ clear\t\tclear the screen." << std::endl
            << "|__ help\t\tdisplay this help." << std::endl;
}

void            Cli::Clear() {
  // Clear the screen.
  if (system("clear") == -1)
    std::cout << "nanotekspice: failed to execute command clear." << std::endl;
}

// ==== Load File
template<typename Out>
void                     Cli::split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> Cli::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

bool            Cli::FileExist(const char *filename)
{
  std::ifstream ifile(filename);

  (void)filename;
  if (ifile.is_open()) { ifile.close();return true; }
  ifile.close();
  return false;
}

std::string     Cli::Trim(const std::string& str,
                          const std::string& whitespace)
{
    size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    size_t strEnd = str.find_last_not_of(whitespace);
    size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string     Cli::EpurString(const std::string& str,
                                const std::string& fill,
                                const std::string& whitespace)
{
    // trim first
    std::string result = Trim(str, whitespace);

    // replace sub ranges
    size_t beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        size_t endSpace = result.find_first_not_of(whitespace, beginSpace);
        size_t range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        size_t newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

char            **VectorToDoubleTab(const std::vector<std::string> &strings) {
  char** cstrings = new char*[strings.size()];

  for(size_t i = 0; i < strings.size(); ++i)
  {
      cstrings[i] = new char[strings[i].size() + 1];
      std::strcpy(cstrings[i], strings[i].c_str());
  }

  return cstrings;
}

void            Cli::Load(const std::string &file) {
  if (file == "load") { Help(); return ; }

  std::vector<std::string> args = split(file, ' ');

  std::cout << "file = '" << args[0] << "'" << std::endl;
  if (!FileExist(args[0].c_str())) {
    std::cout << "nanotekspice: " << file << " is not a file." << std::endl;
    return ;
  }

  args.insert(args.begin(), "");
  char **tab = VectorToDoubleTab(args);

  try {
    Parser  parser(args.size(), tab);

    parser.createTree();
    parser.parseTree(*parser.getRoot());

    this->circuit = parser.getCircuit();
    this->outputs = parser.getOutputs();
    this->clocks = parser.getClocks();
  } catch(std::exception const &err) {
    std::cout << "nanotekspice: " << err.what() << std::endl;
    return ;
  }
}