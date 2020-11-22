/*
Ilia Zarka 9289
Iosif Chrysostomou 9130

The purpose of this file is to load the modeled cpu with a straight forward
series of instructions, to easily compare different types of cpus
**/

//define the number of iterations of the for loop
#define NUMOFITERATIONS 10000

int main()
{

    //initialize the variables
    int i,j=NUMOFITERATIONS;
    float k[4 * NUMOFITERATIONS];

    for (i=0; i<NUMOFITERATIONS; i++){

        //do four simple operations in every iteration of the loop
        k[0+(4*i)]= (float) (i+j);
        k[1+(4*i)]= (float) (i-j);
        k[2+(4*i)]= (float) (i*j);

        if(j==0){
            j=1;
        }
        k[3+(4*i)]=(float)i / (float)j;

        j--;
    }
}
