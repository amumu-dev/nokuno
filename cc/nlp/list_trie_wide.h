#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

struct ListTrieWide {
    typedef pair<wstring, vector<wstring> > Entry;
    typedef vector<Entry> Entries;
    typedef pair<wchar_t, ListTrieWide> Pair;
    typedef list<Pair>::iterator Itr;
    list<Pair> children;
    vector<wstring> values;

    void insert(wstring key, wstring value) {
        if (key.length() != 0) {
            wchar_t first = key[0];
            wstring rest = key.substr(1);
            ListTrieWide *child = find(first);
            if (child == NULL) {
                children.push_back(Pair(first, ListTrieWide()));
                child = &(children.back().second);
            }
            child->insert(rest, value);
        } else {
            values.push_back(value);
        }
    }
    ListTrieWide *find(wchar_t key) {
        for (Itr i = children.begin(); i != children.end(); i++) {
            if (key == i->first) {
                return &i->second;
            }
        }
        return NULL;
    }
    vector<wstring> *search(wstring key) {
        if (!key.length())
            if (values.size())
                return &values;
            else
                return NULL;
        wchar_t first = key[0];
        wstring rest = key.substr(1);
        ListTrieWide *child = find(first);
        if (child != NULL)
            return child->search(rest);
        return NULL;
    }
    void common_prefix_search(wstring query, wstring key, Entries &results) {
        if (values.size())
            results.push_back(Entry(key, values));
        if (!query.length() || !children.size())
            return;
        ListTrieWide *child = find(query.at(0));
        if (child != NULL)
            child->common_prefix_search(query.substr(1), key+query.at(0), results);
    }
    void predictive_search(wstring query, wstring key, Entries &results) {
        if (query.length() <= key.length() && values.size())
            results.push_back(Entry(key, values));
        if (!children.size())
            return;
        if (query.length() > key.length()) {
            wchar_t c = query.at(key.length());
            ListTrieWide *child = find(c);
            if (child != NULL)
                child->predictive_search(query, key+c, results);
        } else {
            for (Itr i = children.begin(); i != children.end(); i++) {
                i->second.predictive_search(query, key+i->first, results);
            }
        }
    }
    void fuzzy_search(wstring query, wstring key, int distance, Entries &results) {
        if (!query.length() && values.size())
            results.push_back(Entry(key, values));
        if (!children.size())
            return;

        // normal match
        if (query.length()) {
            ListTrieWide *child = find(query.at(0));
            if (child != NULL)
                child->fuzzy_search(query.substr(1), key+query.at(0), distance, results);
        }
        // edit operation
        if (distance) {
            // insert
            for (Itr i = children.begin(); i != children.end(); i++) {
                i->second.fuzzy_search(query, key+i->first, distance-1, results);
            }
            if (query.length()) {
                // delete
                fuzzy_search(query.substr(1), key, distance-1, results);

                // substitute
                for (Itr i = children.begin(); i != children.end(); i++) {
                    if (i->first != query.at(0))
                        i->second.fuzzy_search(query.substr(1), key+i->first, distance-1, results);
                }
            }
            // transpose
            if (query.length() > 1) {
                wchar_t c = query.at(0);
                query[0] = query.at(1);
                query[1] = c;
                fuzzy_search(query, key, distance-1, results);
            }
        }
    }
    void fuzzy_search_ex(wstring query, int distance, Entries &results) {
        Entries entries;
        fuzzy_search(query, L"", distance, entries);
        for (int i = 0; i < entries.size(); i++) {
            Entry entry = entries.at(i);
            bool flag = false;
            for (int j = 0; j < results.size(); j++) {
                if (entry.first == results.at(j).first) {
                    flag = true;
                }
            }
            if (!flag) {
                results.push_back(entry);
            }
        }
    }
    void display(wstring key=L"") {
        if (values.size() > 0)
            wcout << key << "\t" << format(values) << endl;
        for (Itr i = children.begin(); i != children.end(); i++) {
            i->second.display(key + i->first);
        }
    }
    static wstring format(Entries entries) {
        wstring result = L"";
        for (int i = 0; i < entries.size(); i++) {
            ListTrieWide::Entry entry = entries.at(i);
            result += entry.first + L"\t";
            for (int j = 0; j < entry.second.size(); j++)
                result += entry.second.at(j) + L" ";
            result += L"\n";
        }
        return result;
    }
    static wstring format(vector<wstring> entries) {
        wstring result = L"";
        for (int i = 0; i < entries.size(); i++)
            result += entries.at(i) + L" ";
        return result;
    }
};

