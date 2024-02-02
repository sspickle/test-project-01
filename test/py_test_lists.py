import sys
import os

import p1_impl as p1

class TestPersonList:

    def test_len_0(self):
        plist = p1.PyPersonList()
        assert plist.size == 0
        del plist


    def test_len_3(self):

        data = (
                (b'Joe',3,4,2012,3.4),
                (b'Sam',1,12,2014,3.9),
                (b'Andy',3,2,2013,2.5),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        assert plist.size == 3
        del plist

    def test_sort_name1(self):

        data = (
                (b'Joe',3,4,2012,3.4),
                (b'Sam',1,12,2014,3.9),
                (b'Andy',3,2,2013,2.5),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        plist.sort(p1.SORT_BY_NAME)
        
        sortedNames = sorted([x[0] for x in data])
        objs = plist.getObjs()
        for i in range(len(data)):
            assert objs[i]['name'] == sortedNames[i]

        del plist

    def test_sort_name2(self):

        data = (
                (b'a',22,7,2001,3.0),
                (b'b',21,7,2001,1.0),
                (b'c',20,7,2001,2.0),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        plist.sort(p1.SORT_BY_NAME)
        
        sortedNames = sorted([x[0] for x in data])
        objs = plist.getObjs()
        for i in range(len(data)):
            assert objs[i]['name'] == sortedNames[i]

        del plist

    def test_sort_date(self):

        data = (
                (b'Joe',3,4,2012,3.4),
                (b'Sam',1,12,2014,3.9),
                (b'Andy',3,2,2013,2.5),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        plist.sort(p1.SORT_BY_DATE)
        
        sortedDates = sorted([x[1]*100+x[2]+x[3]*10000 for x in data])
        
        objs = plist.getObjs()
        for i in range(len(data)):
            dobj = objs[i]['year']*10000 + objs[i]['month']*100 + objs[i]['day']
            assert dobj == sortedDates[i]

        del plist

    def test_sort_gpa(self):

        data = (
                (b'Joe',3,4,2012,3.4),
                (b'Sam',1,12,2014,3.2),
                (b'Andy',3,2,2013,2.5),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        plist.sort(p1.SORT_BY_GPA)
        
        sortedGpas = sorted([x[4] for x in data])
        
        objs = plist.getObjs()
        for i in range(len(data)):
            assert int(objs[i]['gpa']*1000) == int(sortedGpas[i]*1000)

        del plist

    def test_remove(self):

        data = (
                (b'Joe',3,4,2012,3.4),
                (b'Sam',1,12,2014,3.9),
                (b'Andy',3,2,2013,2.5),
            )

        plist = p1.PyPersonList()

        for d in data:
            plist.add(d[0], d[1], d[2], d[3], d[4])
            
        plist.remove(1)
        data = list(data)
        del data[1]
        
        objs = plist.getObjs()
        for i in range(len(data)):
            assert objs[i]['name'] == data[i][0]

        del plist
