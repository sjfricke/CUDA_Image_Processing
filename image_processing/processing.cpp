#include "utils.h"

using namespace cv;
using namespace std;
int average_value(int start, int end)
{
if (end < start) {
	return -1;
}
//input args for the image_data vector 


//vector<Pixel> image_data;
//Pixel current_pixel;
//current_pixel.red

//find average of a pixel range
int sum_red = 0;
int sum_blue = 0;
int sum_green = 0;

for(vector<Pixel>::iterator it = IMAGE_DATA.at(start); it != IMAGE_DATA.at(end); ++it) {
	sum_red += (int) *it.red;
	sum_blue += (int) *it.blue;
	sum_green += (int) *it.green;
}

int avg_red = sum_red / v.size();
int avg_blue = sum_blue / v.size();
int avg_green = sum_green / v.size();

//really not sure about this code.....
/*inline unsigned long average(unsigned long a, unsigned long b) {	
	return (((a^b) & 0xfffefefeUL) >> 1) + (a & b);
} */

//NewColor = sqrt((R1^2+R2^2)/2),sqrt((G1^2+G2^2)/2),sqrt((B1^2+B2^2)/2);

//find total average color first
int xVertex;
int yVertex;
int roiWidth;
int roiHeight;


cout << "xVertex: " << endl;
cin >> xVertex;

cout << "yVertex: " << endl;
cin >> yVertex;

cout << "roiWidth: " << endl;
cin >> roiWidth;

cout << "roiHeight: " << endl;
cin >> roiHeight;

Rect roi(xVertex, yVertex, roiWidth, roiHeight);
Mat image_roi = inputImage(roi);

Scalar avgPixelIntensity = mean(image_roi);

cout << "Pixel Intensity over your ROI = " << avg PixelIntensity.val[0] << endl;

 return 0; 
}
