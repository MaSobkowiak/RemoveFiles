
#include <iostream>
#include <cstdint>
#include <experimental/filesystem>


int main()
{
  if( std::experimental::filesystem::remove( "C:\\Users\\Maciej\\Desktop\\GRAFOWE\\benford - Copy\\434784 - Copy.txt") != 0 )
    perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
  return 0;
}