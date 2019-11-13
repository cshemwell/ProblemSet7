#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h> 

//Compile this code using:
//gcc ProblemSet7.2.c -o 7.2 -lsndfile


#define kBufferSize 4096

int main(void) {
  SNDFILE *inFile = NULL, *outFile = NULL; //pointers to a sound files
	SF_INFO sfInfo; //hold an information about a sound file
  static float buffer[kBufferSize]; //Buffer for holding samples

  //Initialize SF_INFO with 0s (memset is in string.h library)
  memset(&sfInfo, 0, sizeof(SF_INFO));

  //Open the original sound file as read mode
  inFile = sf_open("sine.wav", SFM_READ, &sfInfo);
  if(!inFile){
    printf ("Error : could not open file : sine.wav\n");
		puts (sf_strerror (NULL));
		return 1;
  }
  //Check if the file format is in good shape
  if(!sf_format_check(&sfInfo)){	
    sf_close(inFile);
		printf("Invalid encoding\n");
		return 1;
	}

  //Modify sfInfo if you need to...
  sfInfo.frames = sfInfo.frames * 5;

  //Open another sound file in write mode
  outFile = sf_open("sine10.wav", SFM_WRITE, &sfInfo);

  //Check if the file was succefully opened
  if(!outFile){	
    printf ("Error : could not open file : sine10.wav");
		puts (sf_strerror(NULL));
		return 1;
	}

  //Copy samples from the original file to the new file
  int readcount = 0;
  int outerCounter = 0;
  int totalReadCount = 0;

  // i = i + 1  ==  i += 1  ==  i++ 

  while(outerCounter < 5) {
    readcount = sf_read_float(inFile, buffer, kBufferSize); //reads sample by sample, into buffer, 4096 at a time
    totalReadCount += readcount;

    printf("outerCounter: %d\n",outerCounter);
    printf("readcount: %d\n", readcount);

    sf_write_float(outFile, buffer, readcount); //then writes those 4096 samples into the new file, sf_read goes to next chunk of 4096

    if (readcount == sfInfo.frames / 5){
      sf_seek(inFile, 0, SEEK_SET);
      readcount = 0;
      outerCounter++;
    }
  }
  
  //Close the open files
  sf_close(inFile);
	sf_close(outFile);

  return 0;
}