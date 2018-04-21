import os
import sys

def help():
    print("\tThis script takes a file copied from https://arxiv.org"
            " and turns it into an edge list.")

def usage(h=True):
    print("Usage: [{}] <source_file> <out_file>".format(sys.argv[0])) 
    if h:
        help()
    sys.exit(0)

def get_args():
    try: 
        if "help" in sys.argv[1] or "HELP" in sys.argv[1]:
            usage()
        else:
            papers_file = sys.argv[1]
            out_file = sys.argv[2]
    except Exception as e:
        usage(h=False)
    return papers_file, out_file

def confirm_directory_structure(out_file):
    """
    Utility method to ensure that the directory structure of dir_in
    exists. This method will create all necessary directories if they do not exist.
    """

    dir_list = out_file.split('/')
    if len(dir_list) > 0:
        path = ''
        for d in dir_list[:-1]:
            path = os.path.join(path, d)
            if not os.path.exists(path):
                os.makedirs(path)


def has_all_papers(all_papers, log=True):
    """
    Utility method to ensure that all papers have been found and accounted for.
    """

    i = 1
    for paper in all_papers: 
        if i != paper:
            if log:
                print("Missing paper: {}".format(i))
            return False
        i+=1
    return True

def is_new_paper(line):
    """
    While parsing through the entire input file, this method is used to detect
    when a new paper is being read in. This method is used to help extract
    author information.
    
    A new paper is detected by seeing if a line adheres to the following format:
    [<paper_number>] ...
    Where paper number is any number between 1 and the total number of papers in the file.
    """

    try:
        if line[0] == "[":
            int(line[1:line.find("]")])
            return True
    except:
        return False
    return False

def abbreviate(author):
    """
    Many authors appear on many different papers, with their names taking slightly
    different forms. To alleviate this issue, we abbreviate all authors to the
    folliwing format: first_initial_of_first_name.last_name
    This method abbreviates an author's name in this way, with the first initial of the first name
    taken and appended to the last name.
    Example: abbreviate('John Smith') -> 'J.Smith'
    """
    sp = author.split(' ')
    if len(sp) == 1:
        return author
    ab = sp[0][0] + '.' + sp[-1]
    return ab

FILTERS = ['et al', 'latex', 'request', 'uuencoded', 'file']

def filter_out(author):
    """
    Filter out information that probably is not any author.
    Filtered out fake 'authors' include strings with numbers within them,
    and any strings that contain values featured in the FILTERS list.
    """

    for f in FILTERS:
        if f in author:
            return True
    if any(char.isdigit() for char in author):
        return True
    return False

def clean(line):
    """
    Some author lines have a lot of information contained within parentheses,
    usually indicating what institution the author is associated with.
    This method eliminates all information contained within (), even in the case
    of embedded parenthesis, using stack-like logic.
    """

    while '(' in line:
        l_index = -1
        r_index = -1
        l_count = 0
        r_count = 0
        for i, c in enumerate(line):
            if c == '(': 
                l_count += 1
                if l_count == 1:
                    l_index = i
            if c == ')':
                r_count += 1
                if r_count == l_count:
                    r_index = i
                    line = line[:l_index-1] + line[r_index+1:]
                    break
    return line          

EXTRA = ['and', 'by']
def remove_extra_words(author):
    for word in EXTRA:
        if word in author:
            author = author.replace(word, '')
            if author.startswith(' '):
                author = author[1:]
    return author

def format_authors(line):
    """
    The following method uses all of the utility format methods defined above.
    Author lines are cleaned of any unneccessary information, and returned
    as a list of authors.
    """
    
    line = clean(line)
    authors = line.split(', ')
    authors_out = [abbreviate(remove_extra_words(author)) for author in authors if not filter_out(author)]
    return authors_out

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
if __name__ == "__main__":
    papers_file, out_file = get_args()
    if not os.path.exists(papers_file):
        raise FileNotFoundError("{} does not exist".format(papers_file))
    confirm_directory_structure(out_file)
    i = 1
    with open(papers_file, 'r') as papers, open(out_file, 'w') as out:
        all_papers = []
        author_edges = []
        marker = -1
        for line in papers:
            line = line.rstrip()
            if marker != -1:
                if marker == 0:
                    authors = format_authors(line)
                    author_edges.append(authors)
                    print(i, authors)
                    i+=1
                marker-=1
            elif is_new_paper(line):
                all_papers.append(int(line[1:line.find(']')]))
                marker = 1
        has_all_papers(all_papers)
        interpret_results(author_edges)
