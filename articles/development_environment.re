
= 開発環境

== ホストPC
Spresense SDK・Arduino IDEもMacで開発しました。@<br>{}
OSバージョンは次のとおりです。

 * macOS Big Sur バージョン 11.6.1

Spresens SDK・Arduino IDEともにLinux/Windows/macOSで開発が可能です。

== Spresense SDK
//footnote[spresense_sdk_tutorial][https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html]

Spresense SDKの開発環境構築はCLI・Visual Studio Codeの2つの方法がWebマニュアルに記載されています。
私はSpresense入門時はVisual Studio Codeを使っていましたが、最近はCLIを使っています。
Visual Studio CodeからCLIに変更した理由は次のとおりです。

 * チュートリアル@<fn>{spresense_sdk_tutorial}がCLIを使う前提で書かれているため

Visual Studio Codeを使っても問題ないと思いますが、CLIを使うとチュートリアルに書かれているサンプルプログラムを
素早く確認できると思ったので最近はCLIを使っています。@<br>{}

CLI・Visual Studio Codeともにマニュアルとおりに作業していけば問題なく開発環境を構築できました。
CLIの開発環境構築は次のリンクに書かれています。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html}

Visual Studio Codeの開発環境構築は次のリンクに書かれています。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ide_ja.html}

Spresense SDK・ブートローダーのバージョンは執筆時の最新バージョンである【v2.4.0】を使用しました。


== Arduino IDE
Arduino IDEの開発環境構築は次のリンクに書かれています。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_set_up_ja.html}

私はArduino・ブートローダーのバージョンは執筆時の最新バージョンである【v2.4.0】を使用しました。


