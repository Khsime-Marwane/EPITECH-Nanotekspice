
#!/bin/bash
make -C ./__tests__/
clear
./__tests__/nanotekspice_test
rm -rf ./__tests__/nanotekspice_test
