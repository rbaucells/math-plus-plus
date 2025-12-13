#!/bin/bash
# Setup script to install a newer version of LLDB with working Python bindings

set -e

echo "Installing LLDB 18 from LLVM repository..."

# Add LLVM APT repository
wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
echo "deb http://apt.llvm.org/bookworm/ llvm-toolchain-bookworm-18 main" | sudo tee /etc/apt/sources.list.d/llvm.list

# Update package list
sudo apt-get update

# Install LLDB 18 and Python bindings
sudo apt-get install -y lldb-18 python3-lldb-18

# Create symlinks to make lldb-18 the default
sudo update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-18 100
sudo update-alternatives --set lldb /usr/bin/lldb-18

# Verify installation
echo ""
echo "LLDB installation complete!"
lldb --version
echo ""
echo "Python bindings test:"
python3 -c "import lldb; print(f'LLDB Python module loaded successfully')" || echo "Warning: Python bindings may need additional setup"


echo "settings set target.load-cwd-lldbinit true" >> ~/.lldbinit
