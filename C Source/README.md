# ENGG1410-MiniProject1 - CryptoMagic

Alec and Lukas's source code for ENGG1410 MiniProject 1. It is a C programmed Command Line Interface (CLI) utility.

## [**>> Download latest version here**](https://github.com/Tacitor/ENGG1410-MiniProject1/releases)

### Download and Install

Simply download the latest release [here](https://github.com/Tacitor/ENGG1410-MiniProject1/releases) as a .zip file. Select the version for you computer: Windows x64, or Universal for all. Unzip the folder and then just run it from your computer.

### Bugs and Issues

Please report and bugs or issues on the [issue tracker](https://github.com/Tacitor/ENGG1410-MiniProject1/issues)

### Instructions

The compiled program must be called from the command line. It can take in either 1 or 2 CLI arguments. The arguemnts must be seperated by a space between each parameter.

#### Arguments
  - -E or -D [Used to select either Ecrytion mode or Decrption mode resepctfully. If neither is included then encrytion mode is assumed. If one of the flags is included then it must be the first parameter in the CLI arguments.] [optional]
  - filename [Determins the file what will be operated on.] [required]

### Output

Based on the given input in the form of the CLI arguments, the program will output either the encrypted or decrypted version of the specified file. This output file will be given the same base file name as the one given as input. It will then have the file extension of .txt when decrypting and a .crp file type when encrypting. The output file will be place in the same directory as where the input file is located.
