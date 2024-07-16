from flask import Flask, request, jsonify, render_template
import base64
from PIL import Image
from io import BytesIO

app = Flask(__name__, template_folder='./templates', static_folder='./static')

# Пример данных изображения для демонстрации
demo_image_path = 'received_image.png'

# GET запрос для отображения HTML страницы с изображением
@app.route('/')
def index():
    return render_template('index.html', image_filename=demo_image_path)


# Обработка GET и POST запросов на /receive_image
@app.route('/receive_image', methods=['GET', 'POST'])
def handle_image():
    if request.method == 'GET':
        # Обработка GET запроса, возвращение каких-то данных или HTML
        return jsonify({'message': 'GET запрос на /receive_image'}), 200
    elif request.method == 'POST':
        try:
            # Получение данных из POST запроса в формате JSON
            request_data = request.get_json()

            # Получение изображения из JSON и декодирование из base64
            base64_image = request_data['image']
            image_data = base64.b64decode(base64_image)

            # Сохранение изображения (пример сохранения)
            image = Image.open(BytesIO(image_data))
            image.save('static/received_image.png')

            # Пример ответа сервера
            response = {'message': 'Изображение успешно получено и сохранено'}
            print(jsonify(response))
            return jsonify(response), 200

        except Exception as e:
            print(f"Ошибка при обработке запроса: {str(e)}")
            response = {'message': 'Ошибка при обработке запроса'}
            return jsonify(response), 500


if __name__ == '__main__':
    app.run(debug=True, port=5000)

