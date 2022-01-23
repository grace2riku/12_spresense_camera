
= Arduino IDE開発手順
Arduino IDEでデジタルカメラアプリケーションを開発する手順について書きます。

今回のソースコードは次のGitHubリポジトリに置きました。

@<href>{https://github.com/grace2riku/spresense_camera_arduino/tree/master,Arduino IDE 版デジタルカメラアプリケーション GitHub リポジトリのリンク}

== プログラム概要
ArduinoのカメラサンプルプログラムをベースにしてSpresense SDK同様の動作に変更します。

== ベースにしたサンプルプログラム
Arduinoのカメラサンプルスケッチをベースにします。
カメラのサンプルスケッチの説明は次のリンクに書かれています。

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html#_tutorial_camera,3. Camera チュートリアル}
　こちらはカメラサンプルスケッチに必要なライブラリインストールやコード変更手順など動作手順を解説してます。

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_developer_guide_ja.html#_%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E3%82%B3%E3%83%BC%E3%83%89%E3%81%AB%E3%82%88%E3%82%8B%E8%A7%A3%E8%AA%AC,.2.7. サンプルコードによる解説}
　こちらはカメラサンプルスケッチのコードを詳しく解説しています。

== アプリケーションの作成手順
Arduino版デジタルカメラアプリケーション作成手順について書きます。

@<href>{https://developer.sony.com/develop/spresense/docs/arduino_set_up_ja.html,Spresnse Arduino版の開発環境構築}は完了している前提で書きます。

=== カメラサンプルスケッチの環境構築
前述しましたがArduino版デジタルカメラアプリケーションはカメラのサンプルスケッチをベースに変更していきます。
そのためまずはカメラサンプルスケッチの環境構築をします。
具体的には@<hd>{ベースにしたサンプルプログラム}の【3. Camera チュートリアル】の手順を実行します。
LCD（ILI9341）の制御に必要なライブラリのインストール、LCD制御にサンプルスケッチの変更が必要なためです。

=== カメラサンプルスケッチの動作確認
前の@<hd>{カメラサンプルスケッチの環境構築}で開発環境ができました。
実際にビルド・書込みしカメラサンプルスケッチが正しく動作することを確認します。
カメラサンプルスケッチの動作は次のリンク4, 5に書かれているとおりです。

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html#_%E5%8B%95%E4%BD%9C%E6%89%8B%E9%A0%86_18,3.1.3. 動作手順}

LCD画像にプレビュー画像を表示し、100枚撮影しSDカードに保存します。
この動作が確認できたらArduino版デジタルカメラアプリケーションの変更をしていきます。

//comment{
OSのコンフィギュレーションがないことがSpresense SDKとの違いと書く。
//}

=== 実装
==== ファイル構造
ファイルの構造は次のようになっています。
各ファイルの説明は*印を参照してください。

 * camera_arduino
 ** camera_arduino.ino *1
 ** gpio.h *2
 ** gpio.ino *3

1. カメラメイン処理@<br>{}
　デジタルカメラアプリケーションのメイン機能の処理をおこないます。@<br>{}

2. GPIO.inoヘッダファイル@<br>{}
　GPIO.inoで外部公開する関数を定義しています。@<br>{}

3. 割り込み設定・割り込み処理@<br>{}
　APS学習ボードのタクトスイッチを使用するため割り込み設定、割り込み処理をしています。
デジタルカメラアプリケーションで追加した処理で変更内容は@<hd>{デジタルカメラアプリケーション要求仕様の実装}の
GPIO初期化、GPIO両エッジ割り込みに書いています。@<br>{}

==== カメラアプリケーションのメイン機能
カメラサンプルスケッチから次の変更をします。

 * シリアルポートと接続していないと処理が進まないのをコメント

==== デジタルカメラアプリケーション要求仕様の実装
@<hd>{camera_overview|デジタルカメラの要求仕様}で書いた機能を実装します。

 1. LCDに画像をプレビュー表示し続ける → 【LCD画像プレビュー表示継続機能】とします。
 1. 任意のタイミングで画像を保存できること → 【任意タイミングの画像保存機能】とします。
 1. 任意のタイミングでカメラの使用を終了できること → 【カメラ終了機能】とします。

===== LCD画像プレビュー表示継続機能@<br>{}
カメラサンプルスケッチは100枚画像を撮影・保存したら撮影が終了する処理になっています。
カメラのプレビュー画像をLCDに表示継続するように変更しています。

===== 任意タイミングの画像保存機能@<br>{}
APS学習ボードのスイッチ（SW2）が押されたときのみ画像撮影・保存するように変更しています。

===== カメラ終了機能@<br>{}
Spresense SDK版と違い、Arduino版ではカメラ終了機能は実装していません。
Arduino版はSpresense SDK版と違いベアメタルなアプリケーション（OSのうえで動いていない）ため、
アプリケーション終了しても意味がないかなと思ったためです。

===== GPIO初期化@<br>{}
Sprense SDK版とやっていることは同じですが実装が違います。
Arduino版はArduino用の関数でGPIO初期化（pinMode）・割り込み設定（attachInterrupt関数,、digitalPinToInterrupt関数）しています。
また関数に指定するピン番号もSpresense SDKと異なるので注意が必要です（@<hd>{hardware_overview|ピン配置の注意点}参照）。


===== GPIO両エッジ割り込み@<br>{}
こちらも【GPIO初期化】と同様にSprense SDK版とやっていることは同じですが実装が違います。
割り込み時の入力ピンのレベル読み込みはdigitalRead関数、LED書込みはdigitalWrite関数とArduinoの開発でお馴染みの関数を使用しています。


=== ビルド
Arduino IDEの左上の【検証】ボタンでビルドします。【コンパイルが完了しました。】と表示されていればビルドは正常に完了しています。

== 書込み
USBケーブルのマイクロBと【メインボード】のUSBコネクタを接続します。
Arduino IDEの左上の【マイコンボードに書き込む】ボタンでビルド・書込みします。
【ボードへの書き込みが完了しました。】と表示されていれば書込みは正常に完了しています。

== GitHubソースコードをmakeする手順
デジタルカメラアプリケーションをビルドする手順は次のとおりです。@<br>{}

1. GitHubリポジトリからソースコードをクローン・ダウンロードします。@<br>{}

 * @<href>{https://github.com/grace2riku/mycameraapps,Spresense SDK版デジタルカメラアプリケーション GitHubリポジトリのリンク}

【Download ZIP】を選択しzipファイルをダウンロードした前提で手順をかきます。
次の開発環境構築が終わっていることが前提になります。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_set_up_ja.html,Spresnse Arduino版の開発環境構築}

 * @<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html#_tutorial_camera,3. Camera チュートリアル}

2. ダウンロードしたzipファイルを任意のパスに解凍します。@<br>{}

3. 解凍したディレクトリ名称を次のように変更します。@<br>{}

 * zipファイル解凍したときのフォルダ名（spresense_camera_arduino-master）を【spresense_camera】に変更

スケッチのファイル名（camera_arduino.ino）とディレクトリ名が一致している必要があります。
フォルダ名を変更せずにcamera_arduino.inoをダブルクリックすると次のメッセージが表示されビルドできません。

//image[arduino_dir_name_change][サンプルスケッチのディレクトリ変更]{ 
//}

4. camera_arduino.inoをダブルクリックで開きます。@<br>{}

5. Arduino IDEの左上の【検証】ボタンでビルドします。【コンパイルが完了しました。】と表示されていればビルドは正常に完了しています。


== 動作確認
=== アプリケーションの動作確認

=== Arduino IDE固有のこと
//comment{
シリアルモニタの操作手順

//}