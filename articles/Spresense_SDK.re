
= Spresense SDK開発手順
Spresense SDKでデジタルカメラアプリケーションを開発する手順について書きます。

今回のソースコードは次のGitHubリポジトリに置きました。

 * @<href>{https://github.com/grace2riku/mycameraapps,Spresense SDK版デジタルカメラアプリケーション GitHubリポジトリのリンク}

== プログラム概要
@<hd>{camera_overview|デジタルカメラの要求仕様}で書いたとおり、
ベースにしたサンプルプログラムを次に変更しています。

 1. LCDに画像をプレビュー表示し続ける。
 1. 任意のタイミングで画像を保存できること
 1. 任意のタイミングでカメラの使用を終了できること。

== ベースにしたサンプルプログラム
@<hd>{camera_overview|examples/cameraサンプルプログラムの説明}で書いたとおり、
今回のデジタルカメラアプリケーションはSpresense SDKのサンプルプログラム【examples/camera】をベースにつくりました。

== アプリケーションの作成手順
アプリケーションの作成手順は次のリンク、章に記載されています。
参考にするとアプリケーションの作成の流れが理解できると思います。@<br>{}

@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html}@<br>{}
3. サンプルアプリケーション "Hello, World!" の実行手順@<br>{}

以降にデジタルカメラアプリケーションの作成手順を書きます。

=== インストールしたツールを使用可能にする
後述するコンフィギュレーションツールを使用可能にするため次のコマンドを実行します。

//cmd{
source ~/spresenseenv/setup
//}

=== アプリケーションの追加
アプリケーションの追加の手順はWebマニュアルに次の3つが書かれています。

@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E3%83%A6%E3%83%BC%E3%82%B6%E3%83%BC%E3%82%A2%E3%83%97%E3%83%AA%E3%81%AE%E8%BF%BD%E5%8A%A0%E6%96%B9%E6%B3%95,6. ユーザーアプリの追加方法}@<br>{}

 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_examples%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,examplesに追加する}
 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,別ディレクトリに追加する}
 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E3%83%84%E3%83%BC%E3%83%AB%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%99%E3%82%8B,ツールを使用する}

私は【ツールを使用する】の手順でアプリケーションを追加しました。
以降に具体的操作手順を書きます。@<br>{}

次の手順で使うツールは【spresense/sdk】ディレクトリで実行する必要があるので移動します。
//cmd{
cd spresense/sdk
//}

新規ディレクトリ【mycameraapps】を作成します。
//cmd{
tools/mkappsdir.py mycameraapps "My Camera Apps"
//}

作成したディレクトリにデジタルカメラのアプリケーション【myfirstcameraapp】を追加します。@<br>{}
この【myfirstcameraapp】がNuttXのシェルから指定するコマンド名になります。
//cmd{
tools/mkcmd.py -d mycameraapps myfirstcameraapp "My first camera app"
//}

=== コンフィギュレーション前の準備
デジタルカメラアプリケーションは【examples/camera】サンプルプログラムと同じハードウェア構成になります。
次の手順のコンフィギュレーションは【examples/camera】と同じ設定となるように次のファイルを変更します。

 * /spresense/mycameraapps/myfirstcameraapp/Kconfig

次のリンクを参考にしつつ、【examples/camera】のKconfigファイルと同じように変更します。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_examples%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,Kconfig変更内容参考リンク}

【examples/camera】のKconfigファイルは次のパスにあります。@<br>{}

 * spresense/sdk/apps/examples/camera/Kconfig

最終的に変更したKconfigファイルは次になります。
//list[camera_kconfig][カメラアプリケーションのKconfigファイル]{
config MYCAMERAAPPS_MYFIRSTCAMERAAPP
	tristate "My first camera app"
	default y
	---help---
		Enable the myfirstcameraapp app

if MYCAMERAAPPS_MYFIRSTCAMERAAPP

config MYCAMERAAPPS_MYFIRSTCAMERAAPP_PROGNAME
	string "Program name"
	default "myfirstcameraapp"
	---help---
		This is the name of the program that will be use when the NSH ELF
		program is installed.

config MYCAMERAAPPS_MYFIRSTCAMERAAPP_PRIORITY
	int "myfirstcameraapp task priority"
	default 100

config MYCAMERAAPPS_MYFIRSTCAMERAAPP_STACKSIZE
	int "myfirstcameraapp stack size"
	default 2048

config MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD
	bool "Output to LCD"
	default n
	---help---
		This enables to output the captured RGB565 image to LCD.

endif
//}

Kconfigファイルの変更ポイントとしては次になります。

 * 【examples/camera】サンプルプログラムのKconfigと同様に
 LCD出力有無のコンフィギュレーション項目【MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD】を追加したこと

 * アプリケーションの名称に合わせて各種コンフィグ設定の頭に【MYCAMERAAPPS_MYFIRSTCAMERAAPP】にしていること


=== コンフィギュレーション
NuttX・Spresense SDKのコンフィギュレーションをおこないます。
デジタルカメラアプリケーションに使う機能、デバイス、プロセッサペリフェラルの有効・無効を設定します。@<br>{}
デジタルカメラアプリケーションは【examples/camera】サンプルプログラムと同じハードウェア構成となるので、
【examples/camera】と同じコンフィギュレーション設定にします。
次のコマンドを実行します。

//cmd{
tools/config.py examples/camera
//}

さらに次のコマンドを実行しコンフィギュレーションを設定していきます。
//cmd{
tools/config.py -m
//}

CUIのコンフィギュレーション設定画面が表示されます。
@<list>{camera_kconfig}で作成したKconfigファイルの【MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD】を有効化します。@<br>{}
【Application Configuration】を選択します。

//image[tools_config_py_m_1][tools/config.py -mの実行結果1]{ 
//}

【Spresense SDK】を選択します。

//image[tools_config_py_m_2][tools/config.py -mの実行結果2]{ 
//}

【My Camera Apps】を選択します。

//image[tools_config_py_m_3][tools/config.py -mの実行結果3]{ 
//}

@<list>{camera_kconfig}で追加したLCD有効化のコンフィグ【Output to LCD】が表示されています。@<br>{}

//image[tools_config_py_m_4][tools/config.py -mの実行結果4]{ 
//}

【Output to LCD】にカーソルをあわせてスペースを押下します。
【Output to LCD】に【*】印がマークされます。
//image[tools_config_py_m_5][tools/config.py -mの実行結果5]{ 
//}

次の操作をして@<img>{tools_config_py_m_6}画面に移動し< Yes >を選択します。@<br>{}

 * 右カーソル押下で< Exit >を選択し続ける

 * Escキーを押下し続ける

//image[tools_config_py_m_6][tools/config.py -mの実行結果6]{ 
//}

=== 実装
【examples/camera】のソースコードを流用してデジタルカメラのアプリケーションを実装していきます。

==== ファイル構造
ファイルの構造は次のようになっています。
各ファイルの説明は*印を参照してください。

 * spresense/mycameraapps-master
 ** .built *1
 ** .sdksubdir *1
 ** Make.defs *1
 ** Makefile *1
 ** myfirstcameraapp *1
 *** configs/default/defconfig *1
 *** camera_bkgd.c *2
 *** camera_bkgd.h *2
 *** camera_fileutil.c *2
 *** camera_fileutil.h *2
 *** camera_main.c *3
 *** gpio.c *4
 *** Kconfig *5
 *** Make.defs *1
 *** Makefile *6
 *** myfirstcameraapp_main.c *7


1. 自動生成且つ変更なし@<br>{}
　@<hd>{アプリケーションの追加}で自動生成されるファイルです。変更不要しません。@<br>{}

2. 【examples/camera】サンプルコード。@<br>{}
　サンプルコードをそのまま利用します。変更しません。@<br>{}

3. 【examples/camera】サンプルコード　main処理@<br>{}
　サンプルコードを流用し変更します。変更内容は@<hd>{camera_main.cの変更}、
@<hd>{デジタルカメラアプリケーション要求仕様の実装}に書いています。@<br>{}

4. 割り込み設定・割り込み処理@<br>{}
　APS学習ボードのタクトスイッチを使用するため割り込み設定、割り込み処理をしています。
デジタルカメラアプリケーションで追加した処理で変更内容はGPIO初期化、GPIO両エッジ割り込みに書いています。@<br>{}

5. Kconfig@<br>{}
　自動生成されるファイルです。【examples/camera】を参考にコンフィグ追加します。
変更内容は@<hd>{コンフィギュレーション前の準備}に書いています。@<br>{}

6. Makefile@<br>{}
　自動生成されるファイルです。【examples/camera】のMakefileを参考に変更します。
4のソースコードをビルド対象に追加します。変更内容は@<hd>{Makefileの変更}に書いています。@<br>{}

7. デジタルカメラアプリケーションのメイン関数@<br>{}
　自動生成されるファイルです。main関数からGPIO初期設定、
3の【examples/camera】のmain関数を呼び出しデジタルカメラアプリケーションを開始します。
変更内容は@<hd>{main関数}に書いています。@<br>{}


==== サンプルソースコードの流用
【examples/camera】の次のソースコードをアプリケーションの
ディレクトリ【spresense/mycameraapps/myfirstcameraapp】にコピーします。

 * camera_bkgd.c

 * camera_fileutil.c

 * camera_main.c

 * camera_bkgd.h

 * camera_fileutil.h


【examples/camera】サンプルソースコードは次のディレクトリに格納されています。

 * spresense/sdk/apps/examples/camera


==== camera_main.cの変更
コピーしたcamera_main.cを修正します。
次の項目を変更します。

 * LCD出力のマクロ名称の変更

 * main関数の名称変更

===== LCD出力のマクロ名称の変更@<br>{}
camera_main.cのLCD出力のマクロは【examples/camara】サンプルプログラムで動作することが
前提になっています。
今回デジタルカメラアプリケーション向けにKconfigファイルを修正し、LCD出力のコンフィグを変更しました。

 * 【examples/camara】サンプルプログラムのKconfigファイルのLCD出力のコンフィグ
 ** EXAMPLES_CAMERA_OUTPUT_LCD

 * デジタルカメラアプリケーションのKconfigファイルのLCD出力のコンフィグ
 ** MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD

camara_main.cの【EXAMPLES_CAMERA_OUTPUT_LCD】を【MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD】に置換します。

===== main関数の名称変更@<br>{}
camera_main.cのmain関数の名称を変更します（sdk_camera_example_mainに変更）。
【examples/camara】サンプルプログラムではcamera_main.cのmain関数がアプリケーションの起点でした。
今回のデジタルカメラアプリケーションでは次のファイルのmain関数がアプリケーションの起点になるためです。

 * spresense/mycameraapps/myfirstcameraapp/myfirstcameraapp_main.c

==== main関数
spresense/mycameraapps-master/myfirstcameraapp/myfirstcameraapp_main.cの
main関数に次の処理を追加します。

===== GPIO初期化関数の呼び出し@<br>{}
タクトスイッチのGPIO入力設定・割り込み設定を行うGPIO初期化関数（gpio_init関数）を呼び出します。

===== カメラmain処理関数の呼び出し@<br>{}
myfirstcameraapp_main.cのmain関数からsdk_camera_example_main関数を呼び出し、
デジタルカメラアプリケーションの挙動を開始します。@<br>{}


==== デジタルカメラアプリケーション要求仕様の実装
@<hd>{camera_overview|デジタルカメラの要求仕様}で書いた機能を実装します。

 1. LCDに画像をプレビュー表示し続ける → 【LCD画像プレビュー表示継続機能】とします。
 1. 任意のタイミングで画像を保存できること → 【任意タイミングの画像保存機能】とします。
 1. 任意のタイミングでカメラの使用を終了できること → 【カメラ終了機能】とします。

===== LCD画像プレビュー表示継続機能@<br>{}
exampels/cameraサンプルプログラムの動作を次のように変更しました。

 * コマンドライン引数の撮影画像ファイル数を【1】にしてもプレビュー画像をLCD出力し続けるよう変更

===== 任意タイミングの画像保存機能@<br>{}
APS学習ボードのタクトスイッチ（SW2）押下でjpgでファイル保存する動作に変更しました。
SW2の割り込みハンドラで画像保存のフラグをセットし、メインループでフラグの状態を監視しています。

===== カメラ終了機能@<br>{}
APS学習ボードのタクトスイッチ（SW1）押下でアプリケーションを終了する動作に変更しました。
SW1の割り込みハンドラでアプリケーション終了のフラグをセットし、メインループでフラグの状態を監視しています。

===== GPIO初期化@<br>{}
APS学習ボードのタクトスイッチは次の機能割り当てにしました。

 * SW1はアプリケーションの終了に使用

 * SW2はシャッターに使用

SW1・SW2の押下状況を把握するために両エッジの割り込みを使うことにしました。
ここで割り込みエッジ設定・割り込みハンドラ登録、割り込みの有効化をしています。

===== GPIO両エッジ割り込み@<br>{}
APS学習ボードのタクトスイッチ（SW1、SW2）はプルアップされています。
GPIO初期化でスイッチ押下（立ち下がりエッジ）・リリース（立ち上がりエッジ）の両エッジで割り込み発生するよう設定しています。
SW1押下でアプリケーションの終了のフラグをセットします。SW2押下でシャッターのフラグをセットします。
また、SW1・SW2のレベルを読み込み、読み出したレベルをAPS学習ボードのLED（USER_LED1、USER_LED2）に書込みしています。
結果スイッチ押下でLEDが消灯し、スイッチリリースでLEDが点灯します。

=== make
==== Makefileの変更


== ベースにしたサンプルプログラムの変更点
//comment{

//}

== GitHubソースコードをmakeする手順


== 書込み

== 動作確認
=== アプリケーションの動作確認
=== Spresense SDK固有機能


