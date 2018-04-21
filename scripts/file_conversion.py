import os

FILTERS = ['et al', 'latex', 'request', 'uuencoded', 'file']
EXTRA = ['and', 'by']

def __confirm_directory_structure(out_file):
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


def __has_all_papers(all_papers, log=True):
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

def __is_new_paper(line):
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

def __abbreviate(author):
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


def __filter_out(author):
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

def __clean(line):
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

def __remove_extra_words(author):
    """
    Author lines sometimes feature extra words, like 'and', or 'by'.
    This method will safely remove these words.
    """

    for word in EXTRA:
        if word in author:
            author = author.replace(word, '')
            if author.startswith(' '):
                author = author[1:]
    return author

def __format_authors(line):
    """
    The following method uses all of the utility format methods defined above.
    Author lines are cleaned of any unneccessary information, and returned
    as a list of authors.
    """
    
    line = __clean(line)
    authors = line.split(', ')
    authors_out = [__abbreviate(__remove_extra_words(author)) for author in authors if not __filter_out(author)]
    return authors_out

def __create_edges(authors):
    """
    Given a list of authors who collaborated together on a single paper,
    return a list of tuples that represent edges between all authors.
    The reason we check to see if the two authors are equal is due to an exception
    in the code and an unavoidable issue: some authors lose the uniqueness of their name
    after it is abbreviated (sorry Ka Lok Ng and Kin-Wang Ng).
    """

    pairs = []
    authors = sorted(authors)
    for i in range(len(authors)):
        for j in range(i+1, len(authors)):
            if authors[i] != authors[j]:
                pairs.append((authors[i], authors[j]))
            else:
                print('Duplicate: {}'.format(authors[i]))
    return pairs

def extract_authors_for_testing(papers_file):
    """
    This method can be called when only the python data structures created from the file
    conversion are needed. No output files will be created by calling this file.
    This is useful if you need to examine the filtered-out authors.

    params:
        papers_file : the input text file to be parsed
    return:
        -> a list of all author interactions fetched from file
        -> a list of edges (tuples of size 2) between all authors
    """

    if not os.path.exists(papers_file):
        raise FileNotFoundError("{} does not exist".format(papers_file))
    with open(papers_file, 'r') as papers:
        all_authors = []
        author_edges = []
        marker = -1
        for line in papers:
            line = line.rstrip()
            if marker != -1:
                if marker == 0:
                    authors = __format_authors(line)
                    all_authors.append(authors) 
                    edges = __create_edges(authors)
                    for edge in edges:
                        author_edges.append(edges)
                marker-=1
            elif __is_new_paper(line):
                marker = 1
        return all_authors, author_edges

def convert_to_edgelist_file(papers_file, out_file):
    """
    Given an input file that consists of a list of paper information pulled from https://arxiv.org,
    this method will extract all of the authors who co-wrote papers together and put them together into an edge list.
    The output file parameter provided can be several directories deep, and not exist yet. This method will create
    the output directories as needed.

    params:
        papers_file : the input text file to be parsed
        out_file : the path to write the edge list to
    return
        -> nothing?
    """

    if not os.path.exists(papers_file):
        raise FileNotFoundError("{} does not exist".format(papers_file))
    __confirm_directory_structure(out_file)
    i = 1
    with open(papers_file, 'r') as papers, open(out_file, 'w') as out:
        all_papers = []
        author_edges = []
        marker = -1
        for line in papers:
            line = line.rstrip()
            if marker != -1:
                if marker == 0:
                    authors = __format_authors(line)
                    author_edges.append(authors)
                    edges = __create_edges(authors)
                    for edge in edges:
                        out.write(edge[0] + ' ' + edge[1] + '\n')
                    #print(i, authors)
                    i+=1
                marker-=1
            elif __is_new_paper(line):
                all_papers.append(int(line[1:line.find(']')]))
                marker = 1
        __has_all_papers(all_papers)
