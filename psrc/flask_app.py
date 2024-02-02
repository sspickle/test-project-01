from flask import Flask, Markup, request, render_template
import p1_impl as p1
import subprocess
import string
import traceback
from io import StringIO
app = Flask(__name__)
personList = p1.PyPersonList()

def getTraceback():
    f = StringIO()
    traceback.print_exc(file=f)
    f.seek(0)
    return f.read()

@app.route('/', methods=['GET','POST'])
def home():

    err = "" 
    msgs = []
    
    if request.method == 'POST':
        msgs.append("it's a post")
        keys = list(request.form.keys())
        msgs.append("keys => " + str(keys))
        if 'name' in keys:
            msgs.append('name in keys')
            name = request.form['name']
            bd = request.form['birthdate']
            gpa = request.form['gpa']
            try:
                m, d, y = (int(x) for x in bd.split('-'))
                gpa = float(gpa)
                personList.add(name.encode('utf-8'), m, d, y, gpa)
                msgs.append("Added person!")
            except:
                err = getTraceback()
        else:
            msgs.append('name not in keys')
            try:
                msgs.append('iterating over keys.')
                removeIXs = []
                for key in keys:
                    msgs.append("checking key: " + str(key))
                    if key == "sortName":
                        msgs.append("sorting by name")
                        personList.sort(p1.SORT_BY_NAME)
                        
                    elif key == "sortBirthday":
                        msgs.append("sorting by date")
                        personList.sort(p1.SORT_BY_DATE)
                    
                    elif key == "sortGPA":
                        msgs.append("sorting by gpa")
                        personList.sort(p1.SORT_BY_GPA)

                    elif key[:6] == 'remove':
                        ix = int(key.split('-')[1])
                        removeIXs.append(ix)

                for ix in sorted(removeIXs, key=lambda x: -x): # reverse sort IXs
                    personList.remove(ix)
                    msgs.append("removing index: %d" % ix)
            except:
                err = getTraceback()

    results = personList.getObjs()

    return render_template("display.html", len = len(results), results=results, err=err, msgs = msgs)

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
