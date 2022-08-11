#include "controller/profiter.hpp"
#include "controller/searcher.hpp"
#include "view/console.hpp"
#include <string.h>
#include <iostream>
#include "model/database.hpp"
#include "model/internet.hpp"

int main(int argc, char *argv[])
{
     try
     {
          if (strcmp(argv[1], "--search") == 0)
          {
               if (argc == 3)
               {
                    int seconds = atoi(argv[2]);
                    search_offers(seconds);
               }
               else
               {
                    search_offers(300);
               }
          }
          else if (strcmp(argv[1], "--profit") == 0)
          {
               if (argc == 2)
                    determine_profitation(1, 75);
               else if (argc == 3)
                    determine_profitation(atoi(argv[2]), atoi(argv[2]));
               else if (argc == 4)
                    determine_profitation(atoi(argv[2]), atoi(argv[3]));
               else
                    show_usage();
          }
          else
          {
               show_usage();
               return 1;
          }
     }
     catch (const std::exception &e)
     {
          std::cerr << e.what() << '\n';
     }
}
