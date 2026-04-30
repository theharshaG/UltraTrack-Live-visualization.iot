from flask import Flask, request, jsonify, render_template
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# ---------------- DATABASE ----------------
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///iot.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

# ---------------- MODEL ----------------
class Distance(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    value = db.Column(db.Float)

# create DB
with app.app_context():
    db.create_all()

# ---------------- ROUTES ----------------

# Dashboard
@app.route("/")
def home():
    return render_template("index.html")

# Receive data from ESP32
@app.route("/distance", methods=["POST"])
def receive_distance():
    data = request.get_json()

    distance = data["distance"]

    print("Distance:", distance)

    # 🔥 ALERT LOGIC
    if distance < 10:
        print("⚠️ ALERT: Object too close!")

    new = Distance(value=distance)
    db.session.add(new)
    db.session.commit()

    return jsonify({"msg": "saved"})

# Send data to frontend
@app.route("/distance", methods=["GET"])
def get_distance():
    all_data = Distance.query.all()

    result = []
    for d in all_data:
        result.append({
            "value": d.value
        })

    return jsonify(result)

# ---------------- RUN ----------------
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
