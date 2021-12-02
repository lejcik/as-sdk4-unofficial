# Altap Salamander SDK 4.0 Unofficial

![CodeQL](https://github.com/lejcik/as-sdk4-unofficial/workflows/CodeQL/badge.svg)

The SDK for Altap Salamander 4.0 was not yet published. Here is an unofficial port, however it contains the official sources that I've got from Altap staff.

## Installation and setup

For plugins development I'd recommend staying with the latest public [Altap Salamander SDK](https://www.altap.cz/salamander/downloads/sdk/) **3.08**, which can be downloaded [here](ftp://ftp.altap.cz/pub/altap/salamand/as308sdk.7z) . Once the plugin is stable, you can compile it with this SDK port for **AS 4.0**.

You can build plugins in `Debug` and `Release` configurations. However, the special `SDK` build is not supported, as it requires `salamand.exe` to be compiled with this `SDK` configuration. That's why Salamander binaries are not distributed with this SDK. It contains only source and header files, that are necessary for plugins compilation.

Firstly, try out to compile some of the demo plugins under `salamand\plugins`, they have preconfigured include paths to the `shared` directory. I'd recommend putting your plugin sources there, and maybe reuse the project files from demo plugins. Then you should configure the project properties, and set the *Debugging command* to the path where your `salamand.exe` is installed (depending on CPU architecture, x86 or x64). You can then debug your plugin, which you will load with the *Plugins Manager* in *Salamander* app, that was started by the debugger.

## License

Code licensed under the [Altap License](LICENSE). This are their sources, I have no right to change the license!
