
#!/bin/bash
make -C ./__tests__/
echo "\n\n\n\n"
./__tests__/nanotekspice_test
rm -rf ./__tests__/nanotekspice_test
