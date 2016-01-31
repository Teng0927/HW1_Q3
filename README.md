#Overview
* 用C++完成影像處理的工作：將圖片加上電影濾鏡
* 如何處理整個畫面，包括陰影處、光亮處之對比與色彩調整
* 最佳數值

#Implementation
* 可調整的數值部分：數值越**小**，效果越**大**。
```
	std::cout << "調色(1~5):";
	std::cin >> color;
	std::cout << "對比度(1~5):";
	std::cin >> cons;

	color = color * 10;
	cons = cons * 10;
```
藉由這個部分，可以不更改code內容，<br/>
而直接在執行前輸入想要的數值。

* 調色：電影濾鏡的調色分為陰暗處與光亮處。<br/>
首先，我藉由R,G,B加總數值，來判斷該點為陰暗處或光亮處。
```
a = pixptr[0] + pixptr[1] + pixptr[2];
```
我將陰暗處與光亮處之分界訂在a=390。

  **陰暗處**

```
	b = (390 - a)/color;
				
	if (pixptr[2] < b) pixptr[2] = 0;		//red
	else pixptr[2] = pixptr[2] - b;

	if (pixptr[1]>(255 - b)) pixptr[1] = 255;	//green
	else pixptr[1] = pixptr[1] + b;

	if (pixptr[0]>(255 - b)) pixptr[0] = 255;	//blue
	else pixptr[0] = pixptr[0] + b;
```
由於此濾鏡之陰暗處看起來皆較為偏向藍綠色。<br/>
因此我依照比例將紅色數值降低，藍色與綠色數值調高，來達到此效果。

**光亮處**
```
	b = (a - 390)/color;
	
	if (pixptr[2] < b) pixptr[2] = 0;	//red
	else pixptr[2] = pixptr[2] -b ;
				
	if (pixptr[1] < b) pixptr[1] = 0;	//green
	else pixptr[1] = pixptr[1] -b ;
```
此濾鏡過後的光亮處皆會偏向藍色，因此我將紅色與綠色數值降低，來達到此效果。<br/>
因為要使調整過後的畫面依然自然，所以讓數值依原數值做變化。

* 對比度：使陰暗處顏色更深、光亮處顏色更淺。<br/>
因此我將陰暗處依數值做出類似二次曲線的加深，使其更自然。<br/>

**陰暗處**
```
if (a < 195){
	b = (195-a) / cons;
	b = b*b;
}
else {
	b = (a-195) / cons;
	b = b*b;
}

a = 195 / cons;
a = a*a;

for (k = 0; k < 3; k++){
	if (pixptr[k] < a- b) pixptr[k] = 0;
	else if ((pixptr[k] - a + b)>255) pixptr[k] = 255;
	else pixptr[k] = pixptr[k] - a + b;
}
```

**光亮處**
```
if (a < 578){
	b = (578-a) / cons;
	b = b*b;
}
else {
	b = (a-578) / cons;
	b = b*b;
}

a = 187 / cons;
a = a*a;

for (k = 0; k < 3; k++){
	if ((pixptr[k]+a-b) > 255) pixptr[k] = 255;
	else if (pixptr[k] < (b - a)) pixptr[k] = 0;
	else pixptr[k] = pixptr[k] + a - b;
}
```
先判斷此點的值落在陰暗處的前半段或後半段，再將他與中間值的差除一常數、平方，<br/>
最後再將此數值加上。

* 最佳數值
這個部分也許有點主觀，但經過不少次嘗試之後，<br/>
我認為色度3或4，對比度3時，此濾鏡效果最好。

#Disparity result
* pic_1:<br/>
**Before**
<img src="image/city.jpg" >
**After**
<img src="image/Result_city.png" >

* pic_2:<br/>
**Before**
<img src="image/try.jpg" >
**After**
<img src="image/Result_try.png" >

#Reference
1.  http://photoblog.hk/wordpress/105136/%E5%A6%82%E4%BD%95%E5%9C%A8-ps-%E4%BB%A5%E6%9B%B2%E7%B7%9A-curves-%E6%8B%89%E5%87%BA%E9%9B%BB%E5%BD%B1%E6%84%9F%E8%89%B2%E8%AA%BF
