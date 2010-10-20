#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list_trie_wide.h"

#include <cstdlib>

//ワイド文字列からマルチバイト文字列
//ロケール依存
void narrow(const std::wstring &src, std::string &dest) {
    char *mbs = new char[src.length() * MB_CUR_MAX + 1];
    wcstombs(mbs, src.c_str(), src.length() * MB_CUR_MAX + 1);
    dest = mbs;
    delete [] mbs;
}

//マルチバイト文字列からワイド文字列
//ロケール依存
void widen(const std::string &src, std::wstring &dest) {
    wchar_t *wcs = new wchar_t[src.length() + 1];
    mbstowcs(wcs, src.c_str(), src.length() + 1);
    dest = wcs;
    delete [] wcs;
}


int main(int argc, char *argv[]) {
    // trieを読み込み
    int result;
    string filename, mode = "all";
    setlocale(LC_CTYPE, "");
    locale::global(locale(""));

    while((result = getopt(argc, argv, "f:m:")) != -1) {
        switch(result) {
            case 'f':
                filename = optarg;
                break;
            case 'm':
                mode = optarg;
                break;
        }
    }
    ListTrieWide trie;
    if (filename.length() > 0) {
        wifstream ifs(filename.c_str());
        wstring line, input;
        wcout << "inserting.." << endl;
        while (getline(ifs, line)) {
            size_t pos = line.find('\t');
            if (pos == wstring::npos)
                continue;
            wstring key = line.substr(0, pos);
            wstring value = line.substr(pos+1);
            trie.insert(key, value);
        }
        wcout << "input kana:" << endl;
    } else {
        trie.insert(L"tree", L"value01");
        trie.insert(L"trie", L"value02");
        trie.insert(L"try", L"value03");
        trie.insert(L"tree", L"value04");
        trie.insert(L"tr", L"value05");
        trie.insert(L"trees", L"value06");
        trie.insert(L"tere", L"value06");
        trie.display();
    }

    // ソケット通信
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    int sock;
    int yes = 1;

    char inbuf[2048];

    sock0 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock0 < 0) {
        perror("socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;

    setsockopt(sock0,
            SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

    if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("bind");
        return 1;
    }

    if (listen(sock0, 5) != 0) {
        perror("listen");
        return 1;
    }

    while (1) {
        len = sizeof(client);
        sock = accept(sock0, (struct sockaddr *)&client, &len);
        if (sock < 0) {
            perror("accept");
            break;
        }

        memset(inbuf, 0, sizeof(inbuf));
        recv(sock, inbuf, sizeof(inbuf), 0);
        wstring input;
        string multi = inbuf;
        widen(multi, input);
        wcout << L"input: " << input << endl;

        // trieを検索してレスポンスを生成
        wstring response = L"";
        if (mode == "all" || mode == "search") {
            vector<wstring> *result;
            result = trie.search(input);
            if (result)
                response += ListTrieWide::format(*result);
        }
        if (mode == "all" || mode == "common") {
            ListTrieWide::Entries results;
            trie.common_prefix_search(input, L"", results);
            response +=  ListTrieWide::format(results);
        }
        if (mode == "all" || mode == "predict") {
            ListTrieWide::Entries results;
            trie.predictive_search(input, L"", results);
            response += ListTrieWide::format(results);
        }
        if (mode == "all" || mode == "fuzzy") {
            ListTrieWide::Entries results;
            trie.fuzzy_search_ex(input, 2, results);
            response += ListTrieWide::format(results);
        }
        wcout << L"output: " << response << endl;

        string output;
        narrow(response, output);
        send(sock, output.c_str(), (int)strlen(output.c_str()), 0);

        close(sock);
    }

    close(sock0);

    return 0;
}
