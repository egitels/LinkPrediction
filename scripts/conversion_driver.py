from file_conversion import convert_to_edgelist_file

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

if __name__ == "__main__":
    papers_file, out_file = get_args()
    convert_to_edgelist_file(papers_file, out_file)
