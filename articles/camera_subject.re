
= 課題
今回つくったデジタルカメラアプリケーションの課題について書きます。

== Spresense SDK版の課題
=== アプリケーション実行中はシェルに制御が返らないようになっている件
現状はデジタルカメラアプリケーションを実行するとAPS学習ボードのタクトスイッチ（SW1）を押下しない限りNuttXのシェルに制御が返らないようになっています。
デジタルカメラアプリケーション実行中にNuttXのシェルに制御を返し、NuttXの機能・コマンドを実行できるようにしたいと考えています。
アプリケーション実行中にNuttXの機能・コマンドを使えないのはマルチタスクではないですし、OSを使っているメリットが感じられないと思うためです。
現時点私のスキルでは実現方法・手段がわかりませんが改善したいと思っている点です。

=== Spresense SDKのコンフィギュレーションを素早く行う方法
今回のコンフィギュレーションでは次の指定をしました。

//cmd{
KojinoMacBook-2:sdk k-abe$ tools/config.py examples/camera
KojinoMacBook-2:sdk k-abe$ tools/config.py -m
//}

コンフィギュレーションに【examples/camera】を指定し、
その後のCUIメニューで【examples/camera】のアプリは無効化し、
デジタルカメラアプリケーションのコンフィギュレーションは有効化してコンフィギュレーションしていました。
もっと素早く、的確に要求する機能のコンフィギュレーション設定を把握する・設定する方法があれば知りたいと思いました。

こちらのリンク@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%AE%9A%E7%BE%A9%E6%B8%88%E3%81%BF%E3%82%B3%E3%83%B3%E3%83%95%E3%82%A3%E3%82%AE%E3%83%A5%E3%83%AC%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3defconfig,4.1.2. 定義済みコンフィギュレーション（defconfig）}
にあるように【tools/config.py -i】オプションでサンプルプログラムのコンフィギュレーションを知ることができます。

//cmd{
SpresenseSDK:KojinoMacBook-2:sdk k-abe$ tools/config.py -i examples/camera
=== examples/camera ===
[Description]
This configuration contains required options to use camera example.

[Source path]
examples/camera

[Differences]
-NXFONTS_PACKEDMSFIRST=n
+CXD56_CISIF=y
+CXD56_I2C2=y
+CXD56_SDIO=y
+DRIVERS_VIDEO=y
+EXAMPLES_CAMERA=y
+EXAMPLES_CAMERA_OUTPUT_LCD=y
+LCD_ILI9340=y
+LCD_ILI9340_IFACE0=y
+LCD_ILI9340_IFACE0_RLANDSCAPE=y
+MMCSD_HAVE_WRITEPROTECT=n
+MQ_MAXMSGSIZE=64
+NX=y
+NXFONTS_DISABLE_16BPP=n
+NXFONT_SERIF22X29=y
+NX_BLOCKING=y
+NX_DISABLE_16BPP=n
+SPECIFIC_DRIVERS=y
+VIDEO_ISX012=y
+VIDEO_STREAM=y
//}

【tools/config.py -i】オプションで表示されたコンフィギュレーションは
【tools/config.py -m】実行後のCUI画面で設定していくことになります。
【tools/config.py -i】オプションで表示されたコンフィギュレーションは【/】キー押下で検索できることがわかりました。

次に【examples/camera】サンプルプログラムの【NXFONTS_PACKEDMSFIRST】コンフィギュレーションの検索方法について書きます。
@<img>{tools_config_py_m_top}は【tools/config.py -m】実行で表示されるコンフィギュレーションの最上位の階層です。
//image[tools_config_py_m_top][tools/config.py -mで表示されるコンフィギュレーションの最上位の階層]{ 
//}

@<img>{tools_config_py_m_search}はコンフィギュレーションの最上位の階層で【/】キーを押下した画面です。
//image[tools_config_py_m_search][コンフィギュレーション検索画面]{ 
//}

@<img>{tools_config_py_m_search_NXFONTS_PACKEDMSFIRST}は検索したいコンフィギュレーション【NXFONTS_PACKEDMSFIRST】を
入力した後の画面です。検索したいコンフィギュレーション名称を入力し【< OK >】を押下します。
//image[tools_config_py_m_search_NXFONTS_PACKEDMSFIRST][NXFONTS_PACKEDMSFIRSTの検索]{ 
//}

@<img>{tools_config_py_m_search_result}はコンフィギュレーション【NXFONTS_PACKEDMSFIRST】の検索結果画面です。
検索したコンフィギュレーションの定義されている階層を表示してくれます。
表示している階層に移動し、コンフィギュレーションの設定をおこないます。
//image[tools_config_py_m_search_result][コンフィギュレーションの検索結果の表示]{ 
//}

前述した手順でコンフィギュレーションをひとつずつ検索していけば定義位置は把握できます。
コンフィギュレーションが【examples/camera】のように複数あるとなかなか時間がかかると思うので
素早くコンフィグレーション定義位置を知る方法・コンフィグレーションする方法があれば知りたいと思いました。


== カメラボードのセッティング
Spresense SDK版とArduino版ではカメラボードの取り付け位置が180度ずれています。
たとえばSpresense SDK版のカメラボードのセッティングにするとArduino版ではLCDプレビュー表示が180度ずれてしまいました。
Arduino版のカメラセッティングにした場合も同様にSpresense SDK版はLCDプレビュー表示が180度ずれてしまいました。
どちらかにカメラボードの取り付け位置を決めてしまいプログラム側で正しいLCDプレビュー表示するよう修正が必要と考えています。
