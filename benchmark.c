#define NUMOFITERATIONS 10000

int main()
{
    int i,j=NUMOFITERATIONS;
    float k[4 * NUMOFITERATIONS];

    for (i=0; i<NUMOFITERATIONS; i++){

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
