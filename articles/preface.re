= 前書き

この本はSpresenseでデジタルカメラアプリケーションを作り、得た知見を情報共有できればと思い書きました。
アプリケーションのベースはWebのチュートリアルに書いてあるカメラサンプルプログラムです。
サンプルプログラムを少し変更し、外部ボードのスイッチ押下でLCDに表示されている画像を保存するようにしました。@<br>{}
Spresenseの特徴・魅力である、

 * GPS
 * ハイレゾ
 * マルチコア

は今回利用していませんが、開発の手順はなんとなく理解いただけると思います。
SpsesenseのWebマニュアルはわかりやすく、丁寧に、多くの情報が書かれています。
個人的にわからなかったところ、はまったところも記載するようにしました。@<br>{}
こちらは@<strong>{【Tips】}と記載するのでよければ参照ください。

Spresenseを開発する際にベースになるフレームワークはWebマニュアルでは次の2つが書かれています。

 1. Spresense
 2. Arduino

Spresenseの存在を知り、いろいろ試行錯誤し始めたときから私はSpresense SDKを使用してきました。
今回本を書くにあたり両方の開発手法を書き、比較する形にすればそれぞれの特徴も見えてくるかなと思いました。
その辺りの点も注目して読んでみると面白いかと思います。@<br>{}
わたしはNuttX、Linuxを使用した業務経験はありません。
本書のNuttX、Linuxに関する説明が不十分または冗長、わかりにくかったら申し訳ありませんがご容赦いただけると幸いです。@<br>{}

最後にこの本を手に取り、読んでくださった方がSpresenseの魅力・楽しさに気付くきっかけになれば嬉しいです。
さらに業務課題の解決、個人の電子工作のヒントになる情報が本書から得られれば嬉しい限りです。@<br>{}

素敵なSpresense生活を楽しみましょう♪♪♪

== 免責事項

本書に記載された内容は、情報の提供のみを目的としています。したがって、本書を用いた開発、製作、運用は、必ずご自身の責任と判断によって行ってください。
これらの情報による開発、製作、運用の結果について、著者はいかなる責任も負いません。
