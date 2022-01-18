
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

//image[tools_config_py_m_1][tools/config.py -mの実行結果1]{ 
//}

//image[tools_config_py_m_2][tools/config.py -mの実行結果2]{ 
//}

//image[tools_config_py_m_3][tools/config.py -mの実行結果3]{ 
//}

//image[tools_config_py_m_4][tools/config.py -mの実行結果4]{ 
//}

//image[tools_config_py_m_5][tools/config.py -mの実行結果5]{ 
//}

//image[tools_config_py_m_6][tools/config.py -mの実行結果6]{ 
//}

=== 実装
//comment{

//}
=== タクトスイッチ
==== ファイル構造

=== make
==== Makefileの変更
==== Make.defsの確認


== ベースにしたサンプルプログラムの変更点
//comment{

//}

== GitHubソースコードをmakeする手順


== 書込み

== 動作確認
=== アプリケーションの動作確認
=== Spresense SDK固有機能


