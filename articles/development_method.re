
= 開発手法の説明
繰り返しになりますがSpresenseは

 * Spresense SDK

 * Arduino IDE

 の2つの開発方法があります。

 それぞれ特徴があります。
 私がそれぞれの開発手法を試した所感を紹介します。

== Spresense SDK

Arduino IDEとの大きな違いとしてRTOS【NuttX】をベースに動作していることがあると思います。
@<img>{sdk_overview}はSpresense SDKの構造です。

次のリンクのSpresense SDK 開発ガイド -> 1. Spresense SDKの概要 図 2. SDK Overviewより引用@<br>{}
@<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html}

//image[sdk_overview][Spresense SDKの構造]{ 
//}

NuttXベースで動作する恩恵として次があると思います。

 * Linuxライクなコマンドが使える
 
 * POSIXインターフェースが提供されている

【Linuxライクなコマンドが使える】ですがアプリケーションをビルドしたあとに【help】コマンドを確認するとわかります。

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
//}

ファイル・フォルダ編集のコマンドからお馴染みのLinuxコマンドが列挙されています。

【POSIXインターフェースが提供されている】ですが次のリンクの記事が詳しいです。@<br>{}

@<href>{https://www.aps-web.jp/academy/amp/18510/,リアルタイムOS「NuttX」のPOSIXインタフェースを活用してソフトウェアを簡単に移植する}

 * POSIXインターフェースのためアプリケーションの移植が容易

 * PThreadsプログラムを移植が容易

6コアのSpresenseとしてマルチスレッドを容易に実現できる仕組みが提供されているのはよいと思います。


== Arduino IDE
Arduino IDEの使いどころとしてはNuttXが不要な小規模なアプリケーションを開発するときに有用だと思います。
サッと素早くPoCするなど素早くアイデアを形にするときに効果を発揮すると思います。
Spresense以外のマイコンと同じ操作手順でアプリケーションをビルド・書込み・シリアルでモニタリングできることは
メリットがあると思います。

