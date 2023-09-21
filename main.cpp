#include <stdio.h>
#include <stdlib.h>
#include <libserialport.h>

#define BAUD 9600

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	/*Variables for camera function*/
	int n = 0;
	char filename[200];
	string window_name = "video | q or esc to quit";
	Mat frame;
	/*Setup camera and check for camera*/
	namedWindow(window_name);
	VideoCapture cap(0);
	if (!cap.isOpened())
	{

		cout << "cannot open camera";
	}

	/*Variables for serial comms */
	struct sp_port *port;
	int err;
	int key = 0;
	char cmd;

	/* Set up and open the port */
	/* check port usage */
	if (argc < 2)
	{
		/* return error */
		fprintf(stderr, " Port use\n");
		exit(1);
	}

	/* get port name */
	err = sp_get_port_by_name(argv[1], &port);
	if (err == SP_OK)
		/* open port */
		err = sp_open(port, SP_MODE_WRITE);
	if (err != SP_OK)
	{
		/* return error */
		fprintf(stderr, " Can't open port %s\n", argv[1]);
		exit(2);
	}

	/* set Baud rate */
	sp_set_baudrate(port, BAUD);
	/* set the number of bits */
	sp_set_bits(port, 8);

	/* specify the command to send to the port */
	cmd = 1;

	/* set up to exit when q key is entered */
	while (key != 'q')
	{
		cap >> frame;

		/*The code contained here reads and outputs a single pixel value at (10,15)*/
		Vec3b intensity = frame.at<Vec3b>(10, 15);
		int blue = intensity.val[0];
		int green = intensity.val[1];
		int red = intensity.val[2];
		cout << "Intensity = " << endl
			 << " " << blue << " " << green << " " << red << endl
			 << endl;
		/*End of modifying pixel values*/

		/*The code contained here modifies the output pixel values*/
		/* Modify the pixels of the RGB image */
		for (int i = 150; i < frame.rows; i++)
		{
			for (int j = 150; j < frame.cols; j++)
			{
				/*The following lines make the red and blue channels zero
				(this section of the image will be shades of green)*/
				frame.at<Vec3b>(i, j)[0] = 0;
				frame.at<Vec3b>(i, j)[2] = 0;
			}
		}
		/*End of modifying pixel values*/

		imshow(window_name, frame);
		char key = (char)waitKey(25);
		/* write the number "cmd" to the port */
		sp_blocking_write(port, &cmd, 1, 100);

		switch (key)
		{
		case 'q':
		case 'Q':
		case 27: // escape key
			return 0;
		case ' ': // Save an image
			sprintf_s(filename, "filename%.3d.jpg", n++);
			imwrite(filename, frame);
			cout << "Saved " << filename << endl;
			break;
		default:
			break;
		}
	}
	/* close the port */
	sp_close(port);
	return 0;
}