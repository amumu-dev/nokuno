#include "edit.h"

#define LIMIT (50000000)

int main() {
  cout << "Content-Type:text/plain;\r\n\r\n";

  // output query itself
  string query = parse_query(urldecode(getenv("QUERY_STRING")));
  run(query, LIMIT);
  return 0;
}
