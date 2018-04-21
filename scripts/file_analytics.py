from file_conversion import extract_authors_for_testing 

class EdgeCorrector:

    def __init__(self, edge_list):
        self.edge_list = edge_list
        self.counts = self.__count_authors()
  
    def get_anomalies(self): 
        return {"last_name_only" : [key for key in self.counts if len(key.split('.')) == 1],
                "first_char_lower" : [key for key in self.counts if key[0].islower()], 
                "all_upper" : [key for key in self.counts if key.isupper()]}
    def correct_edgelist(self, log=True):
        """
        Find all authors who are listed with only a last name within edgelist, and attempt to
        find their full name, as it appears elsewhere in the paper archive. Returns the updated
        edgelist.
        """
        
        corrected, _ = self.__guess_full_names()
        for edge in self.edge_list:
            for i in range(len(edge)):
                if edge[i] in corrected:
                    old_edge = edge[i] 
                    self.counts[old_edge] -= 1
                    edge[i] = corrected[edge[i]] 
                    self.counts[edge[i]] += 1
                    if self.counts[old_edge] == 0:
                        del self.counts[old_edge]
                    if log:
                        print("Changed {} to {}".format(old_edge, edge[i]))
        return self.edge_list
    
    def __guess_full_names(self): 
        """
        Authors are sometimes listed with only their last name.
        More often than not, these authors also exist elsewhere within the archive with their full name.
        This method attempts to find the full name of an author given only their last name,
        by traversing all authors extracted from the file conversion procedure.
        Since some authors share the same last name, this method sometimes encounters naming
        conflicts. This method keeps track of any naming conflicts and returns them,
        along with the corrected names. If conflicts do occur, the author who appeared
        in more papers takes precedence.

        params:
            counts : the dictionary of counts of each author occurrence
            author_list : the list of all author collaborations
        return:
            -> a dictionary of the guessed corrected names
            -> a dictionary of naming conflicts
        """

        keys = [key for key in self.counts if len(key.split('.')) == 1]
        conflicts = {key:set([]) for key in keys}
        corrected = {}
        for edge in self.edge_list:
            for author in edge:
                sp = author.split('.')
                if len(sp) > 1:
                    for key in keys:
                        if sp[1] == key:
                            conflicts[key].add(author)
                            if key in corrected and corrected[key] != author:
                                if self.counts[author] > self.counts[corrected[key]]:
                                    corrected[key] = author
                            else:
                                corrected[key] = author
        return corrected, {k : conflicts[k] for k in conflicts if len(conflicts[k]) > 1}

    def __count_authors(self):
        d = {}
        for edge in self.edge_list:
            for author in edge:
                if author not in d:
                    d[author]=1
                else:
                    d[author]+=1
        return d

def analyze_data():
    edge_list = extract_authors_for_testing('data/as-ph/1994.txt')
    corrector = EdgeCorrector(edge_list)
    print(corrector.get_anomalies())
    edge_list = corrector.correct_edgelist() 
    print(corrector.get_anomalies())
    

analyze_data()
