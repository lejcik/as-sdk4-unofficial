# Open Salamander SDK 5.0 Unofficial

![CodeQL](https://github.com/lejcik/as-sdk4-unofficial/workflows/CodeQL/badge.svg)

The [Open Salamander 5.0](https://github.com/OpenSalamander) (former _Altap Salamander_) has been released as open-source. Here is an unofficial port of SDK for plugins development.

## Setup

Try out to compile some of the demo plugins under `salamand\plugins`, they have preconfigured include paths to the `shared` directory. I'd recommend putting your plugin sources there, and maybe reuse the project files from demo plugins. Then you should configure the project properties, and set the _Debugging command_ to the path where your `salamand.exe` is installed (depending on CPU architecture, x86 or x64). You can then debug your plugin, which you will load with the _Plugins Manager_ in _Salamander_ app, that was started by the debugger.

## License

Code licensed under the [GPLv2](LICENSE).
