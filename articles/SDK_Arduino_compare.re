
= Spresense SDKとArduino IDEの比較
デジタルカメラアプリケーションをSpresense SDKとArduinoで実装してみました。
Arduino、Spresense SDKの特徴が書かれている次のリンクも参照しつつ、個人的な所感をまとめてみます。

 * @<href>{https://developer.sony.com/develop/spresense/docs/introduction_ja.html#_spresense_%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6,3. Spresense ソフトウェアについて}
 ** 3.1. Spresense Arduino Libraryを用いた開発環境
 ** 3.2. Spresense SDKを用いた開発環境

== 開発の難易度
Arduino、Spresense SDKの特徴を書きます。

 * Arduino
 ** Arduinoを使ったことがある人なら比較的容易に開発することができそう。

 * Spresense SDK
 ** コンフィギュレーションなどArduinoに比べて開発の難易度が高い

Arduino、Spresnse SDKの大きな違いは【OSコンフィギュレーション】の有無かと思いました。
実装したい機能要求により機能の有効化・無効化を選択する作業はOSレスの開発をメインにしている私にとっては練習が必要と感じました。

== 機能面
3. Spresense ソフトウェアについて

リンク: @<href>{https://developer.sony.com/develop/spresense/docs/introduction_ja.html#_spresense_%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6,3. Spresense ソフトウェアについて}の記述を引用します。

 * Spresense SDKはSpresenseがもつ性能を最大限引き出すことができる

今回のデジタルカメラアプリケーションでは次の機能を使用しました。

 * カメラ

 * LCD描画

 * 外部割り込み

これらの機能はSpresense SDK・Arduino両方で使えたので機能面で差があるようには感じませんでした。
機能面で差があるかもしれないと感じたこと理由のひとつとして【チュートリアルの掲載数】です。

@<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html,Arduino チュートリアル}の
章の数は【8】個なのに対して、
@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html,Spresense SDK チュートリアル}の
章の数は【27】個でした。

【Spresense SDKはSpresenseがもつ性能を最大限引き出すことができる】ため多くの機能を紹介しているのかもしれないと思いました。
Linuxコマンドと同じようなコマンドを使えることもSpresense SDKの強みかと思いました。

== 開発したプログラムの移植の容易性
@<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_camera,Spresense SDK 開発ガイド}を
見ていて感じたことですがSpresense SDKはプログラムの移植が容易かもしれないと思いました。
ここでいう移植は次の定義です。

 1. Spresense SDKで開発したプログラムをLinuxに移植するケース
 2. Linuxで移植したプログラムをSpresenseに移植するケース

Spresense SDK チュートリアルを見ていると次の記述がありました。

 * Spresense SDK 開発ガイド 5.4. Camera
 ** Camera制御では、Linuxでお馴染みのV4L2に非常によく似たドライバI/Fを提供しており、V4L2を用いたコードからの流用をしやすくしている

 * 5.6. GNSS
 ** POSIX 準拠のデバイスファイルでアプリケーションから操作することができる

 * 5.7. ASMP Framework
 ** MP message queue は POSIX の message queue に似たメッセージ交換用のインターフェース

こちらの記事にもPOSIXインタフェースを活用した移植について書かれています。

 * @<href>{https://www.aps-web.jp/academy/amp/18510/,リアルタイムOS「NuttX」のPOSIXインタフェースを活用してソフトウェアを簡単に移植する}

LinuxのV4L2に非常によく似たドライバI/F、POSIX I/Fを使用したプログラミングを行うことで前述の移植性を高めることができるのではないかと思いました。

== まとめ
いくつかの観点でSpresense SDKとArduinoを比較してみました。
求められる機能、性能、開発コスト、プログラムの移植性、その他の観点で総合的に判断しプロジェクトに最適な開発手法を選定・選択すればよいと感じました。

