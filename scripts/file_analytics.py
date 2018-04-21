from file_conversion import extract_authors_for_testing 

#doesn't do anything yet
def analyze_data():
    author_list, author_edges = extract_authors_for_testing('data/as-ph/1994.txt')

#doesn't do anything yet
def interpret_results(author_edges):
    d = {}
    for authors in author_edges:
        for author in authors:
            if author not in d:
                d[author] = 1
            else:
                d[author]+=1

    #print(sorted(d.items(), key=lambda x:x[1]))
    
    #keys = sorted(d.keys())
    #for key in keys:
        #print(key, d[key])

    [print(key, d[key]) for key in d if len(key.split('.')) == 1]
