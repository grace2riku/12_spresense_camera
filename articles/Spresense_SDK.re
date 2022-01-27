
= Spresense SDK開発手順
Spresense SDKでデジタルカメラアプリケーションを開発する手順について書きます。

今回のソースコードは次のGitHubリポジトリに置きました。@<br>{}

 * @<href>{https://github.com/grace2riku/mycameraapps,【リンク】Spresense SDK版デジタルカメラアプリケーション GitHubリポジトリ}

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

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html}@<br>{}
 
3. サンプルアプリケーション "Hello, World!" の実行手順@<br>{}

以降にデジタルカメラアプリケーションの作成手順を書きます。

=== インストールしたツールを使用可能にする
後述するコンフィギュレーションツールを使用可能にするため次のコマンドを実行します。

//cmd{
source ~/spresenseenv/setup
//}

=== アプリケーションの追加
アプリケーションの追加の手順はWebマニュアルに次の3つが書かれています。@<br>{}

@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E3%83%A6%E3%83%BC%E3%82%B6%E3%83%BC%E3%82%A2%E3%83%97%E3%83%AA%E3%81%AE%E8%BF%BD%E5%8A%A0%E6%96%B9%E6%B3%95,【リンク】6. ユーザーアプリの追加方法}@<br>{}

 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_examples%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,【リンク】examplesに追加する}
 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,【リンク】別ディレクトリに追加する}
 1. @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E3%83%84%E3%83%BC%E3%83%AB%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%99%E3%82%8B,【リンク】ツールを使用する}

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

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_examples%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B,【リンク】Kconfig変更内容参考リンク}

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

//image[tools_config_py_m_Application_Configuration][Application Configurationを選択]{ 
//}

【Spresense SDK】を選択します。

//image[tools_config_py_m_Spresense_SDK][Spresense SDKを選択]{ 
//}

【My Camera Apps】を選択します。

//image[tools_config_py_m_My_Camera_Apps][My Camera Appsを選択]{ 
//}

@<list>{camera_kconfig}で追加したLCD有効化のコンフィグ【Output to LCD】が表示されています。@<br>{}

//image[tools_config_py_m_disp_Output_to_LCD][Output to LCD]{ 
//}

【Output to LCD】にカーソルをあわせてスペースを押下します。
【Output to LCD】に【*】印がマークされます。
//image[tools_config_py_m_sel_Output_to_LCD][Output to LCDの選択]{ 
//}

次の操作をして@<img>{tools_config_py_m_Examples}画面に移動します。

 * 右カーソル押下で< Exit >を選択し続ける

 * Escキーを押下し続ける

//image[tools_config_py_m_Examples][Examplesの選択]{ 
//}
【Examples】を選択します。

次の@<img>{tools_config_py_m_Camera_example}画面になります。

//image[tools_config_py_m_Camera_example][Camera exampleがマーク]{ 
//}

コンフィギュレーションで次の【examples/camera】を指定したので【Camera example】に*印がマークされています。

//cmd{
tools/config.py examples/camera
//}

 @<strong>{【Tips】}@<br>{}
 今回のデジタルカメラアプリケーションは【examples/camera】サンプルプログラムとハードウェア要件も同じです。
そのため【examples/camera】サンプルプログラムのコンフィギュレーションを指定しました。
こちらの【Camera example】を有効化したままにすると次の2つがアプリケーションとして登録されることになります。

 * デジタルカメラアプリケーション

 * 【examples/camera】サンプルプログラム

FlashROM容量の節約・類似のアプリケーションは2つも必要ないため【Camera example】を無効化します。

次の@<img>{tools_config_py_m_Camera_example_unmark}画面になります。

//image[tools_config_py_m_Camera_example_unmark][Camera exampleを無効化]{ 
//}


再び次の操作をして@<img>{tools_config_py_m_save}画面に移動し< Yes >を選択します。@<br>{}

 * 右カーソル押下で< Exit >を選択し続ける

 * Escキーを押下し続ける

//image[tools_config_py_m_save][コンフィギュレーションの保存]{ 
//}
これでコンフィギュレーションが保存できます。


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
デジタルカメラアプリケーションで追加した処理で変更内容は@<hd>{デジタルカメラアプリケーション要求仕様の実装}の
GPIO初期化、GPIO両エッジ割り込みに書いています。@<br>{}

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

=== ビルド
コンフィギュレーション、コードの変更が終了したらMakefileを変更しmakeします。

==== Makefileの変更
【examples/camera】サンプルプログラムのコードを流用するので、【examples/camera】のMakefileを参照し、
デジタルカメラアプリケーションのMakefileも変更します。
【examples/camera】サンプルプログラムのMakefileは次のパスにあります。@<br>{}

 * spresense/sdk/apps/examples/camera/Makefile

最終的にMakefikeは@<list>{camera_app_makefile}にしました。

//list[camera_app_makefile][デジタルカメラアプリケーションのMakefile]{
include $(APPDIR)/Make.defs
#include $(SDKDIR)/Make.defs
#include $(TOPDIR)/Make.defs

PROGNAME = $(CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_PROGNAME)
PRIORITY = $(CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_PRIORITY)
STACKSIZE = $(CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_STACKSIZE)
MODULE = $(CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP)

ifeq ($(CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD),y)
CSRCS += camera_bkgd.c
endif

CSRCS += camera_main.c camera_fileutil.c gpio.c

#ASRCS =
#CSRCS =
MAINSRC = myfirstcameraapp_main.c

include $(APPDIR)/Application.mk
//}

変更したのはCSRCSになります。@<br>{}
LCD出力のコンフィグ（CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD）が設定されていたときの条件も追加しています。@<br>{}
【examples/camera】サンプルグラムのMakefileではMAINSRCがcamera_main.cになっていました。
今回はデジタルカメラアプリケーションの名称【myfirstcameraapp】で自動生成された【myfirstcameraapp_main.c】を
MAINSRCになっています。camera_main.cはCSRCSに設定しています。

追加したgpio.cはCSRCSに設定しています。

====[column]Kconfigファイルで定義したシンボルの参照
Webマニュアルに書いてありますがKconfigファイルで定義したシンボルはMakefileで参照できます。@<br>{}

Kconfigファイルのシンボル@<br>{}
config MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD@<br>{}

上のシンボルはMakefileでは頭に【CONFIG_】をつけた名称で参照可能です。@<br>{}
CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD@<br>{}

頭に【CONFIG_】をつけたシンボル名はソースファイルでも参照可能です。@<br>{}
【CONFIG_MYCAMERAAPPS_MYFIRSTCAMERAAPP_OUTPUT_LCD】はコンフィギュレーション・make実行後に作成される
次のヘッダーファイルに定義されています。

 * spresense/nuttx/include/nuttx/config.h

ソースコードで参照するには次の@<list>{config_symbol_include}のようにします。

//list[config_symbol_include][Kconfigファイルのシンボルが定義されているインクルードファイル]{
#include <nuttx/config.h>
//}

camera_main.c先頭でもインクルードしています。

Kconfigのシンボルで機能を分ける・ソースコードの処理を分ける、などに使えそうですね。

====[/column]

==== make
makeを実行します。

//cmd{
KojinoMacBook-2:sdk k-abe$ make
//}

次のメッセージが表示されていれば正しくmakeできています。
//cmd{
File nuttx.spk is successfully created.
Done.
//}

【nuttx.spk】がSpresenseに書き込むファイルです。


== GitHubソースコードをmakeする手順
デジタルカメラアプリケーションをmakeする手順は次のとおりです。
Visual Studio Codeのターミナル、シェルで操作することを前提にしています。

1. GitHubリポジトリからソースコードをクローン・ダウンロードします。@<br>{}

 * @<href>{https://github.com/grace2riku/mycameraapps,【リンク】Spresense SDK版デジタルカメラアプリケーション GitHubリポジトリ}

【Download ZIP】を選択しzipファイルをダウンロードした前提で手順をかきます。
Spresense SDKの開発環境構築が終わっていることが前提になります。@<br>{}

2. ダウンロードしたzipファイルを解凍します。@<br>{}

3. 解凍したディレクトリ【mycameraapps-master】をSpresense開発環境構築したディレクトリにコピーします。@<br>{}
　私の場合（Mac）は次がコピー先になります。@<br>{}

 * /Users/ユーザー名/spresense

4. spresense/sdkディレクトリに移動します。@<br>{}

5. ツールを使用するために次のコマンドを実行します。
//cmd{
KojinoMacBook-2:sdk k-abe$ source ~/spresenseenv/setup
//}

6. コンフィギュレーションします。
//cmd{
KojinoMacBook-2:sdk k-abe$ tools/config.py examples/camera
KojinoMacBook-2:sdk k-abe$ tools/config.py -m
//}
@<hd>{コンフィギュレーション}に図で書いてとおりにコンフィギュレーションを設定・保存します。

7. makeします。
//cmd{
KojinoMacBook-2:sdk k-abe$ make
//}

次のメッセージが表示されていれば正しくmakeできています。
//cmd{
File nuttx.spk is successfully created.
Done.
//}

== カメラボードのセッティング
カメラの向きを設定します。

拡張ボードとカメラボードを@<img>{spresense_sdk_camera_setting}のように組み立てます。
//image[spresense_sdk_camera_setting][デジタルカメラ正面]{ 
//}

LCD実装面側は@<img>{spresense_sdk_camera_setting_lcd}のようになります。
//image[spresense_sdk_camera_setting_lcd][デジタルカメラLCD正面]{ 
//}

このカメラボードのセッティング、プログラムの組み合わせで@<img>{spresense_sdk_lcd_preview}のように
LCDにプレビュー画像が表示されます。

== 書込み
makeでできたファイル（nuttx.spk）をメインボードに書込みます。

=== USBシリアルのポート名の確認
書込みツールでUSBシリアルのポート名を指定するので次のコマンドで調べます。
USBケーブルのマイクロBと【メインボード】のUSBコネクタを接続します。
拡張ボードにもUSBコネクタがありますがメインボードと接続します。
USBケーブルを接続したら次のコマンドを実行します。

//cmd{
KojinoMacBook-2:sdk k-abe$ ls /dev/cu.usb*
/dev/cu.usbserial-14140
//}
私のメインボードの場合、【/dev/cu.usbserial-14140】となります。

=== 書込みコマンド実行
書込みはツール（tools/flash.sh）を利用します。次のコマンドで書込みを実行します。
次の表示のようになっていれば書込みは成功しています。メインボードが再起動します。

//cmd{
KojinoMacBook-2:sdk k-abe$ tools/flash.sh -c /dev/cu.usbserial-14140 nuttx.spk
>>> Install files ...
install -b 115200
Install nuttx.spk
|0%-----------------------------50%------------------------------100%|
######################################################################

214304 bytes loaded.
Package validation is OK.
Saving package to "nuttx"
updater# sync
updater# Restarting the board ...
reboot
//}


== 動作確認
次のコマンドを実行しデジタルカメラアプリケーションが動いているか確認します。

=== シリアル接続
シリアルターミナルでNuttXのシェルに接続します。
今回はシリアルターミナルに【minicom】を使用します。

次のコマンドで接続します。
//cmd{
KojinoMacBook-2:sdk k-abe$ minicom -D /dev/cu.usbserial-14140 -b 115200
//}

通信条件は次のとおりです。minicomの場合はボーレートだけを設定すればよいようです。

 * ボーレート: 115200

 * データ長: 8bit

 * パリティ: なし

 * ストップbit: 1


接続できると次のようにNuttXのシェル（nsh）が表示されます。
//cmd{
Welcome to minicom 2.8

OPTIONS: 
Compiled on Jan  4 2021, 00:04:46.
Port /dev/cu.usbserial-14140, 00:19:25

Press Meta-Z for help on special keys


NuttShell (NSH) NuttX-10.1.0
nsh> 
//}


=== アプリケーションの動作確認
デジタルカメラアプリケーションの動作確認をします。
【help】コマンドを実行します。実行できるコマンド・アプリケーションが表示されます。
【Builtin Apps:】にデジタルカメラアプリケーションの【myfirstcameraapp】が表示されています。

//cmd{
nsh> help
help usage:  help [-v] [<cmd>]

  .          cmp        false      ls         nslookup   sleep      usleep     
  [          dirname    free       mkdir      poweroff   source     xd         
  ?          date       help       mkfatfs    ps         test       
  basename   dd         hexdump    mkfifo     pwd        time       
  break      df         ifconfig   mkrd       reboot     true       
  cat        echo       ifdown     mksmartfs  rm         uname      
  cd         exec       ifup       mount      rmdir      umount     
  cp         exit       kill       mv         set        unset      

Builtin Apps:
  myfirstcameraapp  nsh               sh                
//}

【myfirstcameraapp】を入力し、デジタルカメラアプリケーションを開始します。
次のメッセージが表示され、LCDにカメラのプレビュー画像が表示されます。


//cmd{
nsh> myfirstcameraapp
nximage_listener: Connected
nximage_initialize: Screen resolution (320,240)
Take 10 pictures as JPEG file in /mnt/sd0 after 5 seconds.
 After finishing taking pictures, this app will be finished after 10 seconds.
//}

LCDに@<img>{spresense_sdk_lcd_preview}のようにカメラの撮影画像がプレビュー表示されます。
//image[spresense_sdk_lcd_preview][デジタルカメラアプリケーションLCD画像表示]{ 
//}

APS学習ボードのタクトスイッチ（SW2）を押下します。
次はSW2を3回押下したときにシェルに表示されるメッセージです。

//cmd{
sw2_status = 0
Start captureing...
sw2_status = 1
FILENAME:/mnt/sd0/VIDEO001.JPG
Finished captureing...
sw2_status = 0
Start captureing...
sw2_status = 1
FILENAME:/mnt/sd0/VIDEO002.JPG
Finished captureing...
sw2_status = 0
Start captureing...
sw2_status = 1
FILENAME:/mnt/sd0/VIDEO003.JPG
Finished captureing...
//}

表示されているメッセージについて説明します。

 * sw2_status = 0
　APS学習ボードのSW2を押下したときに表示されるメッセージです。このときUSER_LED2は消灯しています。

 * Start captureing...
　LCDに表示されている画像を撮影開始するメッセージです。

 * sw2_status = 1
　APS学習ボードのSW2を押下→リリースしたときに表示されるメッセージです。このときUSER_LED2は消灯→点灯になります。

 * FILENAME:/mnt/sd0/VIDEO001.JPG
　Finished captureing...@<br>{}
　撮影した画像を表示されているパスに保存し、撮影が終了したことを表示しています。


APS学習ボードのタクトスイッチ（SW1）を押下します。
次はSW1を押下・リリースしたときにシェルに表示されるメッセージです。
LCDプレビュー表示の更新が止まり、デジタルカメラアプリケーションが終了します。
シェルのプロンプト（nsh>）が表示されます。

//cmd{
sw1_status = 0
sw1_status = 1
nsh> 
//}

=== Spresense SDK固有機能
デジタルカメラアプリケーションの他に組み込まれているコマンドを確認していみます。
各種コマンドは【help】コマンドで確認できます。

//cmd{
nsh> help
help usage:  help [-v] [<cmd>]

  .          cmp        false      ls         nslookup   sleep      usleep     
  [          dirname    free       mkdir      poweroff   source     xd         
  ?          date       help       mkfatfs    ps         test       
  basename   dd         hexdump    mkfifo     pwd        time       
  break      df         ifconfig   mkrd       reboot     true       
  cat        echo       ifdown     mksmartfs  rm         uname      
  cd         exec       ifup       mount      rmdir      umount     
  cp         exit       kill       mv         set        unset      

Builtin Apps:
  myfirstcameraapp  nsh               sh                
//}

【uname】コマンドを実行してみます。
NuttXのバージョン、ビルド日時が表示されます。
//cmd{
nsh> uname -a
NuttX  10.1.0 b02a66b25b-dirty Jan 20 2022 08:41:05 arm spresense
//}

【ls】コマンドでさきほど撮影した画像ファイルが記録されているか調べてみます。
VIDEO001.JPG、VIDEO002.JPG、VIDEO003.JPGが記録されていました。
//cmd{
nsh> ls mnt/sd0
/mnt/sd0:
 System Volume Information/
 VIDEO001.JPG
 VIDEO002.JPG
 VIDEO003.JPG
 test.txt
//}

【cat】、【echo】コマンドでファイル読み込み、書込みしてみます。
事前にPCでテキストファイル作成しSDカードに書込みしておきます（ファイル名はtest.txt）。
【cat】コマンドでファイルを読み込みしてみます。
//cmd{
nsh> cat /mnt/sd0/test.txt
test file.
Create by Mac.
//}

【echo】コマンドでファイルに追記してみます。
//cmd{
nsh> echo Hello, Spresense!!! >> /mnt/sd0/test.txt
//}

【cat】コマンドで【echo】コマンドで書き込みした内容が書き込まれているか確認してみます。
【echo】コマンドで書込みした「Hello, Spresense!!!」が読み込めました。
//cmd{
nsh> cat /mnt/sd0/test.txt
test file.
Create by Mac.
Hello, Spresense!!!
//}

【ps】コマンドでプロセスの一覧を表示します。
//cmd{
nsh> ps
  PID GROUP PRI POLICY   TYPE    NPX STATE    EVENT     SIGMASK   STACK   USED  FILLED COMMAND
    0         0 FIFO     Kthread N-- Ready              00000000 001024 000464  45.3%  Idle Task
    1       224 RR       Kthread --- Waiting  Signal    00000000 002008 000596  29.6%  hpwork
    2       100 RR       Kthread --- Waiting  Signal    00000000 002008 000332  16.5%  lpwork
    3       100 RR       Kthread --- Waiting  Signal    00000000 002008 000332  16.5%  lpwork
    4       100 RR       Kthread --- Waiting  Signal    00000000 002008 000332  16.5%  lpwork
    6       200 RR       Task    --- Waiting  MQ empty  00000000 000976 000400  40.9%  cxd56_pm_task
    7       100 RR       Task    --- Running            00000000 008152 001144  14.0%  init
//}

【df】コマンドを実行してみます。
ストレージの空き容量が表示されます。@<br>{}
【/mnt/spif】はFlashROMです。
//cmd{
nsh> df -h
  Filesystem    Size      Used  Available Mounted on
  vfat         7493M       12M      7480M /mnt/sd0
  smartfs         4M       28K      4068K /mnt/spif
  procfs          0B        0B         0B /proc
//}

【free】コマンドでメモリの利用状況を表示します。
//cmd{
nsh> free
                     total       used       free    largest
        Umem:      1341536      44784    1296752    1295808
//}

如何でしょうか?一部ですがコマンド実行結果を書きました。
Linuxと同じようにコマンドが実行できました。
