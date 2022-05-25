"""
Лаб. №5. Вариант №25.

Разработать интерактивную web-программу для рисования конечно-элементной сетки по данным таблиц nodes и elements базы данных femdb. 
При указании мышью двух узлов сетки должен прорисовываться отрезок прямой линии между этими узлами с указанием его длины в мировых координатах. 
Примечание. Для указания узлов не должно требоваться абсолютно точное "попадание" курсора в них.
"""

from flask import Flask, render_template, make_response, request, redirect
from database import work_with_db
from sql_provider import SQLProvider

app = Flask(__name__)

# TODO добавить
db_config = {
    'host': '127.0.0.1',
    'user': 'root',
    'password': '',
    'db': ''
}

provider = SQLProvider('sql')


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return redirect("/")
    return render_template("index.html")


@app.route("/points", methods=["GET"])
def get_points():
    sql_req = provider.get("get_all_nodes.sql")
    points = work_with_db(db_config, sql_req)

    return make_response({
        "data": points
    }, 200)


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=7777, debug=True)
