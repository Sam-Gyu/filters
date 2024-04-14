/*
author1:Menna Moustafa Mohamed        ID:20230425         filter:1-4-7-10
author2:Merehan Ibraheem Elmotasem    ID:20230435         filter:2-5-8-11
author3:Sama Waleed Mohammed          ID:20231076         filter:3-6-9-12
 */
#include <iostream>
#include <fstream>
#include <limits>
#include "image_class.h" // Assuming you have defined your Image class in "image_class.h"
using namespace std;

void filter1(string file_name) {
    Image image(file_name);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;
            }
        }
    }
    image.saveImage(file_name);
    cout << "complete!";
}

void filter2(string file_name) {
    Image image(file_name);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= image.channels;
            unsigned int color = (avg < 128) ? 0 : 255;
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = color;
            }
        }
    }
    image.saveImage(file_name);
    cout << "complete!";
}

void filter3(string file_name) {
    int flipped_number;
    cout << "How would you like to flip the image?\n";
    cout << "1. Flipped Vertical\n";
    cout << "2. Flipped Horizontally\n";
    cin >> flipped_number;
    while (flipped_number != 1 && flipped_number != 2) {
        cout << "Invalid input. Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> flipped_number;
    }

    Image image(file_name);
    Image temp(file_name);
    if (flipped_number == 1) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    temp(i, j, k) = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp(i, j, k);
                }
            }
        }
    } else if (flipped_number == 2) {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    temp(i, j, k) = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp(i, j, k);
                }
            }
        }
    }
    image.saveImage(file_name);
    cout << "complete!";
}

void filter4(string file_name) {
    Image image(file_name);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Invert pixel value
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    image.saveImage(file_name);
    cout << "complete!";
}

void filter5(string file_name) {
    int dark_night;
    cout << "How would you like to darken or lighten the image?\n";
    cout << "1. Lighten image\n";
    cout << "2. Darken image\n";
    cin >> dark_night;
    while (dark_night != 1 && dark_night != 2) {
        cout << "Invalid input. Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> dark_night;
    }

    Image image(file_name);
    if (dark_night == 1) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_value = image(i, j, k);
                    pixel_value += static_cast<int>((255 - pixel_value) * 0.25);
                    image(i, j, k) = pixel_value;
                }
            }
        }
    } else if (dark_night == 2) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int avg = 0;
                for (int k = 0; k < image.channels; ++k) {
                    avg += image(i, j, k);
                }
                avg = avg / (3 * 2); // Divide by 6 to average the pixels
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = avg;
                }
            }
        }
    }
    image.saveImage(file_name);
    cout << "complete!";
}
void filter6(string file_name){
        int x, y, a, b;
        Image image(file_name);
        cout << "Enter the coordinates (x y) and offsets (a b): ";
        cin >> x >> y >> a >> b;
        Image image2(x, y);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                for (int k = 0; k < 3; ++k) {

                    if (i + a >= 0 && i + a < image.width &&
                        j + b >= 0 && j + b < image.height) {
                        image2(i, j, k) = image(i + a, j + b, k);
                    } else {


                        image2(i, j, k) = 0;
                    }
                }
            }
        }



    image2.saveImage(file_name);
    cout << "complete!";
}
void filter7(string file_name) {
    Image image(file_name);

    char choice;
    cout << "1. Simple frame\n2. Fancy frame\n";
    cout << "Enter your choice: ";
    cin >> choice;
    while (choice != 1 && choice != 2) {
        cout << "Invalid input. Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
    }

    if (choice == 1) {
        int width = image.width;
        int height = image.height;
        double borderFraction = 0.02;
        int borderSize = static_cast<int>(min(width, height) * borderFraction);


        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (i < borderSize || i >= width - borderSize || j < borderSize || j >= height - borderSize) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 255;
                }
            }
        }


        image.saveImage(file_name);
    } else if (choice == 2) {
        int width = image.width;
        int height = image.height;
        double borderFraction = 0.02;
        int borderSize = static_cast<int>(min(width, height) * borderFraction);
        int lineWidth = 2;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (i < borderSize || i >= width - borderSize || j < borderSize || j >= height - borderSize) {
                    image(i, j, 0) = 0;   // Red channel
                    image(i, j, 1) = 0;   // Green channel
                    image(i, j, 2) = 255; // Blue channel

                    if ((i >= borderSize - lineWidth && i < width - borderSize + lineWidth) &&
                        (j >= borderSize - lineWidth && j < height - borderSize + lineWidth)) {
                        image(i, j, 0) = 255; // Red channel
                        image(i, j, 1) = 255; // Green channel
                        image(i, j, 2) = 255; // Blue channel
                    }
                }
                if ((i >= borderSize + lineWidth && i < width - borderSize - lineWidth) &&
                    (j >= borderSize + lineWidth && j < height - borderSize - lineWidth)) {
                    if ((i < borderSize + lineWidth * 2 || i >= width - borderSize - lineWidth * 2) ||
                        (j < borderSize + lineWidth * 2 || j >= height - borderSize - lineWidth * 2)) {
                        image(i, j, 0) = 255;
                        image(i, j, 1) = 255;
                        image(i, j, 2) = 255;
                    }
                }
            }
        }


        image.saveImage(file_name);
    }
    cout << "complete!";
}

void filter8 (string file_name){
    Image image(file_name);

    const int kernelSize = 40;
    const int halfKernel = kernelSize / 2;

    for (int x = halfKernel; x < image.width - halfKernel; x++) {
        for (int y = halfKernel; y < image.height - halfKernel; y++) {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            for (int i = -halfKernel; i <= halfKernel; i++) {
                for (int j = -halfKernel; j <= halfKernel; j++) {
                    sumRed += image(x + i, y + j, 0);
                    sumGreen += image(x + i, y + j, 1);
                    sumBlue += image(x + i, y + j, 2);
                }
            }

            image(x, y, 0) = sumRed / (kernelSize * kernelSize);
            image(x, y, 1) = sumGreen / (kernelSize * kernelSize);
            image(x, y, 2) = sumBlue / (kernelSize * kernelSize);
        }
    }
    image.saveImage(file_name);
    cout << "complete!";


}
void filter9(string file_name){
    int x, y;
    Image image(file_name);

    cout << "Enter the dimensions (x y): ";
    cin >> x >> y;
    if (isalpha(x) || isalpha(y)) {
        cout << "Invalid input. Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> x >> y;
    }

    Image image2(x, y);

    for (int i = 0; i < x ; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < 3; ++k) {
                image2(i , j , k) = image(i *(image.width/x) , j *(image.height/y) , k);
            }
        }
    }
    image2.saveImage(file_name);
    cout << "complete!";
}

void filter10 (string file_name){
        Image image(file_name);
        char choice;
        cout << "1. Rotate image 270 degrees.\n2. Rotate image 180 degrees.\n3. Rotate image 90 degrees.\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in the input buffer
    while (choice != 1 && choice != 2 && choice != 3) {
        cout << "Invalid input. Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
    }

    if (choice == 1 || choice == 2 || choice == 3) {
        int newWidth, newHeight;
        if (choice == 1 || choice == 2) {
            newWidth = image.height;
            newHeight = image.width;
        } else if (choice == 3) {
            newWidth = image.width;
            newHeight = image.height;
        }

        Image rotatedImage(newWidth, newHeight);

        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    if (choice == 1) {
                        rotatedImage(i, j, k) = image(image.width - j - 1, i, k);
                    } else if (choice == 2) {
                        rotatedImage(i, j, k) = image(image.width - i - 1, image.height - j - 1, k);
                    } else if (choice == 3) {
                        rotatedImage(i, j, k) = image(j, image.height - i - 1, k);
                    }
                }
            }
        }

        rotatedImage.saveImage(file_name);
    }

    cout << "complete!";


}

void filter11(string file_name,string file2_name){
    Image image1(file_name);
    Image image2(file2_name);

    // Merge images
    int newWidth = min(image1.width, image2.width);
    int newHeight = min(image1.height, image2.height);

    Image mergedImage(newWidth, newHeight);

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Calculate the average pixel value from both images
                mergedImage(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
    mergedImage.saveImage(file_name);
    cout << "complete!";





}
void filter12(string file_name){

        Image image(file_name);
        Image tempImage(file_name);

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    int sum = 0;
                    sum += -1 * image(std::max(i - 1, 0), std::max(j - 1, 0), k);
                    sum += -1 * image(std::max(i - 1, 0), j, k);
                    sum += -1 * image(std::max(i - 1, 0), std::min(j + 1, image.height - 1), k);
                    sum += -1 * image(i, std::max(j - 1, 0), k);
                    sum += 8 * image(i, j, k);
                    sum += -1 * image(i, std::min(j + 1, image.height - 1), k);
                    sum += -1 * image(std::min(i + 1, image.width - 1), std::max(j - 1, 0), k);
                    sum += -1 * image(std::min(i + 1, image.width - 1), j, k);
                    sum += -1 * image(std::min(i + 1, image.width - 1), std::min(j + 1, image.height - 1), k);

                    sum = std::min(std::max(sum, 0), 255); // Clipping
                    tempImage(i, j, k) = sum;

                    // Invert the pixel value
                    tempImage(i, j, k) = 255 - tempImage(i, j, k);
                }
            }
        }


        tempImage.saveImage(file_name);


    cout << "complete!";

}
int main() {
    string file_name;
    string file2_name;
    int filter_number;
    cout << "---- Welcome to the Photoshop Program ----\n";
    while (true) {
        cout << "Enter the name of the image you want to modify: ";
        getline(cin, file_name);
        ifstream file_stream(file_name);
        if (!file_stream.good()) {
            cout << "Error: Unable to open file. Please enter a valid file name.\n";
            continue;
        }

        file_stream.close();
        break;
    }
    while (true){
        cout << "\nplease enter a number between (1:15):\n";
        cout << "Filter 1: Grayscale Conversion\n";
        cout << "Filter 2: Black and White\n";
        cout << "Filter 3: Flip Image\n";
        cout << "Filter 4: Invert Image\n";
        cout << "Filter 5: Darken and Lighten Image\n";
        cout << "Filter 6: Crop Images\n";
        cout << "Filter 7: Adding a Frame to the Picture\n";
        cout << "Filter 8: Blur Images\n";
        cout << "Filter 9: Resizing Images\n";
        cout << "Filter 10: Rotate Image\n";
        cout << "Filter 11: Merge Images \n";
        cout << "Filter 12: Detect Image Edges\n";
        cout << "13. Save Modifications\n";
        cout << "14. Enter a New Image\n";
        cout << "15. Exit\n";
        cin>>filter_number;
        if (cin.fail() || filter_number < 1 || filter_number > 15) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " INVALID INPUT \n";
            continue;

        }
        if (filter_number == 1) {
            filter1(file_name);
        }
        else if (filter_number == 2) {
            filter2(file_name);
        }
        else if (filter_number == 3) {
            filter3(file_name);
        }
        else if (filter_number == 4) {
            filter4(file_name);
        }
        else if (filter_number == 5) {
            filter5(file_name);
        }
        else if (filter_number == 6) {
            filter6(file_name);
        }
        else if (filter_number == 7) {
            filter7(file_name);
        }
        else if (filter_number == 8) {
            filter8(file_name);
        }
        else if (filter_number == 9) {
            filter9(file_name);
        }
        else if (filter_number == 10) {
            filter10(file_name);
        }
        else if (filter_number == 11) {
            string file2_name;
            cout << "Enter the second image file name: ";
            getline(cin, file2_name);
            filter11(file_name, file2_name);
        }
        else if (filter_number == 12) {
            filter12(file_name);
        }
        else if (filter_number == 13) {
            Image image(file_name);
            string new_file_name;
            cout << "Please enter your new file name: ";
            cin >> new_file_name;
            image.saveImage(new_file_name);
            system(new_file_name.c_str());
            cout << "Modified image saved as: " << new_file_name << endl;
        }
        else if (filter_number == 14) {
            cout << "Enter the name of the new image you want to modify: ";
            cin >> file_name;
            continue;
        }
        else if (filter_number == 15) {
            cout << "Thank you for using the Photoshop Program.\n";
            break;
        }

    }


    return 0;
}

