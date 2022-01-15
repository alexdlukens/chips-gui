# chips-gui
GUI interface for FPGA endeavours via Chipyard, Freedom-E-SDK, and associated commands

## So Far
- Settings are persistent
- Chipyard/fpga path & freedom-e-sdk paths shown in settings
- terminal output shown in textOutput QWidget

## What's Next
- Specify more Environment variables needed to run chipyard design runs (e.g. vivado env file, $RISCV path, openocd path, etc)
- Allow for editing of FPGA Configs inside window (drag and drop config fragments)
- Graphical device tree representation
- Better layout of components in QT

## End Goal
- Reduce the barrier to entry for generating SoC's using Chipyard
- Provide single, automated installation for Chipyard and closely related projects
- Comprehensive documentation and troubleshooting info
