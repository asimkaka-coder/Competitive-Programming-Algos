#include<stdint.h>
#include<stdio.h>
#include<inttypes.h>


int main()
{
    uint32_t physical_address, offset, starting_address;
    int page_number,page_size=4096;
    while(1){
    printf("Enter Physical Address: ");
    scanf("%" SCNd32, &physical_address);

  
    page_number = physical_address / page_size;

    offset = physical_address % page_size;
    starting_address = physical_address - offset;

    printf("Page Number: %d\n", page_number);
    printf("Offset: %lu\n",(unsigned long) offset);
    printf("Starting Physical Address: %X\n", starting_address);
}
    return 0;
}
