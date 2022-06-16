
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class CSVReader
{
  public:
    CSVReader(){}
    static std::vector<std::vector<std::string>> readCSV(std::string filename)
    {
      std::vector<std::vector<std::string>> playlist{};

      // open file
      std::ifstream file{filename};
      if (file.is_open())
      {
        std::cout << "File opened! " << filename << std::endl;
		DBG("File opened! " << filename);

      // read it one line at a time
        std::string line{};
        while(std::getline(file, line))
        {
          std::cout << "Read line: " << line << std::endl;
		  DBG("Read line: " << line);

          // tokenise the line into a vector of strings
          std::vector<std::string> parts = CSVReader::tokenise(line, ',');
          // append the vector of strings to the playlist
          std::cout << "Read " << parts.size() << " parts " << std::endl;
		  DBG("Read " << parts.size() << " parts ");
          playlist.push_back(parts);
        }
        
        file.close();
      }
      else {// file not open
        std::cout << "Could not open file " << filename << std::endl;
		DBG("Could not open file " << filename);
      }
      return playlist;
    }

  static std::vector<std::string> tokenise(std::string csvLine, char separator)
  {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
      start = csvLine.find_first_not_of(separator, 0);
      do{
          end = csvLine.find_first_of(separator, start);
          if (start == csvLine.length() || start == end) break;
          if (end >= 0) token = csvLine.substr(start, end - start);
          else token = csvLine.substr(start, csvLine.length() - start);
          tokens.push_back(token);
      start = end + 1;
      }while(end > 0);
    return tokens; 
  }
};

/*
int main()
{
  std::string filename{"playlist.csv"};
  std::vector<std::vector<std::string>> playlist = 
  CSVReader::readCSV(filename);
}
*/