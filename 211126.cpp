# include <iostream>
# include <fstream>
# include <string>
# include <sstream>
using namespace std;

class GenerationZero{
    protected:
        static int **arr;
        static int img_number_count;
        static string img_name;
        string img_type="", img_height="", img_width="", img_max_rgb="";
        int int_img_height, int_img_width; 

    private:
        void generateArray(string img_name)
        {           
            string img_red, img_green, img_blue;
            int int_img_red, int_img_green, int_img_blue;

            // Reading the headder info of the ppm file.
            ifstream curr_gen;
            string suff=".ppm";
            //cout<<img_name+suff<<endl;
            curr_gen.open(img_name+suff);
            curr_gen >> img_type;
            curr_gen >> img_height;
            curr_gen >> img_width;
            curr_gen >> img_max_rgb;
            stringstream height_stream(img_height);
            stringstream width_stream(img_width);
            height_stream >> int_img_height;
            width_stream >> int_img_width;

            //cout<<"Height: "<<int_img_height<<"\nWidth: "<<int_img_width<<endl;

            //int_img_height=stoi(img_height);
            //int_img_width=stoi(img_width);
            
            // Creating a 2d array describing the state of the current generation.
            arr = new int*[int_img_height+2];
            for(int i=0; i<int_img_height+2; i++)
            {
                arr[i] = new int[int_img_width+2];
            }

            // Initializing the entire array as 0
            for(int i=0; i<int_img_height+2; i++)
            {
                for(int j=0; j<int_img_width; j++)
                {
                    arr[i][j]=0;
                }
            }

            // Setting up the array according to the passed image
            for(int i=1; i<=int_img_height; i++)
            {
                for(int j=1; j<=int_img_width; j++)
                {
                    curr_gen >> img_red;
                    curr_gen >> img_green;
                    curr_gen >> img_blue;
                    stringstream red_stream(img_red);
                    stringstream green_stream(img_green);
                    stringstream blue_stream(img_blue);
                    red_stream >> int_img_red;
                    green_stream >> int_img_green;
                    blue_stream >> int_img_blue;
                    //int_img_red = stoi(img_red);
                    //int_img_green = stoi(img_green);
                    //int_img_blue = stoi(img_blue);

                    if(int_img_red==0 && int_img_green==0 && int_img_blue==0)
                    {
                        arr[i][j]=1;
                    }
                    else{
                        arr[i][j]=0;
                    }
                }
            }

            curr_gen.close();
        }

    public:
        GenerationZero()
        {
            string img_red, img_green, img_blue;
            int int_img_red, int_img_green, int_img_blue;

            // Reading the headder info of the ppm file.
            ifstream curr_gen;
            string suff=".ppm";
            //cout<<img_name+suff<<endl;
            curr_gen.open(img_name+suff);
            curr_gen >> img_type;
            curr_gen >> img_height;
            curr_gen >> img_width;
            curr_gen >> img_max_rgb;
            stringstream height_stream(img_height);
            stringstream width_stream(img_width);
            height_stream >> int_img_height;
            width_stream >> int_img_width;
        }
        GenerationZero(string name){
            img_name=name;
            generateArray(img_name);
            //img_number_count=1;
        }
};

class NextGeneration : public GenerationZero{
    private:
        string img_name_suffix=to_string(img_number_count);

        void nextGenArray()
        {
            int neighbour_count;
            int **tmp_arr;
            tmp_arr = new int*[int_img_height+2];
            for(int i=0; i<int_img_height+2; i++)
            {
                tmp_arr[i] = new int[int_img_width+2];
            }

            for(int i=0; i<int_img_height+2; i++)
            {
                for(int j=0; j<int_img_width+2; j++)
                {
                    tmp_arr[i][j]=arr[i][j];
                }
            }

            for(int i=1; i<=int_img_height; i++)
            {
                for(int j=1; j<=int_img_width; j++)
                {
                    neighbour_count=tmp_arr[i-1][j-1]+tmp_arr[i-1][j]+tmp_arr[i-1][j+1]+tmp_arr[i][j-1]+tmp_arr[i][j+1]+tmp_arr[i+1][j-1]+tmp_arr[i+1][j]+tmp_arr[i+1][j+1];
                    if(neighbour_count<2 || neighbour_count>3)
                    {
                        arr[i][j]=0;
                    }
                    if(neighbour_count==3)
                    {
                        arr[i][j]=1;
                    }
                }
            }

            for(int i=0; i<int_img_height+2; i++)
            {
                delete[] tmp_arr[i];
            }
            delete[] tmp_arr;
        }

        void createNextGenImg()
        {
            string suff=".ppm";
            string next_gen_img_name=img_name+img_name_suffix+suff;
            ofstream next_gen_img;

            next_gen_img.open(next_gen_img_name);
            next_gen_img << img_type << endl;
            next_gen_img << img_height << " " << img_width << endl;
            next_gen_img << img_max_rgb << endl;

            for(int i=1; i<=int_img_height; i++)
            {
                for(int j=1; j<=int_img_width; j++)
                {
                    if(arr[i][j]==1)
                    {
                        next_gen_img << "0 0 0" << endl;
                    }
                    else{
                        next_gen_img << "255 255 255" << endl;
                    }
                }
            }

            next_gen_img.close();
        }
        
    public:
        NextGeneration()
        {
            nextGenArray();
            createNextGenImg();
            img_number_count++;
            //cout<<img_number_count<<endl;
        }

};

int **GenerationZero::arr;
int GenerationZero::img_number_count=1;
string GenerationZero::img_name;

void lambda()
{
    NextGeneration tmp;
}

int main(void)
{
    GenerationZero("pattern");
    NextGeneration tmp[20];
    GenerationZero("gosperGliderGun");
    NextGeneration tmp2[20];
    return 0;
}