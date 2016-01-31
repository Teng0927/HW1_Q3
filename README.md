#Overview
* 用C++完成影像處理的工作：將圖片加上電影濾鏡
* 如何處理整個畫面，包括陰影處、光亮處之對比與色彩調整
* 最佳數值

#Implementation

* 可調整的數值部分：數值越低，效果越大。
```
	std::cout << "調色(1~5):";
	std::cin >> color;
	std::cout << "對比度(1~5):";
	std::cin >> cons;

	color = color * 10;
	cons = cons * 10;
```
藉由這個部分，可不需調整code內容，而直接在執行前輸入想要的數值。

* 調色：電影濾鏡的調色分為陰暗處與光亮處。<br/>
因此首先，我們藉由R,G,B加總數值，來判斷該點為陰暗處或光亮處。
```
a = pixptr[0] + pixptr[1] + pixptr[2];
```
我將陰暗處與光亮處之分界訂在a=390。


```
if (a < 390){
				b = (390 - a)/color;
				
				if (pixptr[2] < b) pixptr[2] = 0;		//red
				else pixptr[2] = pixptr[2] - b;

				if (pixptr[1]>(255 - b)) pixptr[1] = 255;
				else pixptr[1] = pixptr[1] + b;		//green

				if (pixptr[0]>(255 - b)) pixptr[0] = 255;
				else pixptr[0] = pixptr[0] + b;		//blue
```
陰暗處看起來皆較為偏向藍綠色。
因此我依照比例將紅色數值降低，藍色與綠色數值調高。

