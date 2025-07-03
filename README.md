## Özellikler

- **Qt Framework ile GUI Geliştirme:** QWidget tabanlı arayüz mimarisi kullanılarak dinamik butonlar ve etkileşimli kullanıcı bileşenleri oluşturulmuştur.
- **Zaman Kontrollü Oyun Mekanikleri:** Qt'nin `QTimer` sınıfı kullanılarak belirli aralıklarla ekranda yeni nesneler (karpuzlar) oluşturulmakta ve bu nesnelerin konumları rasgele ayarlanmaktadır.
- **Fare Etkileşimi ile Kesme Algoritması:** `QPushButton` üzerinden kullanıcı tıklamaları algılanarak karpuzların kesilip kesilmediği kontrol edilmekte, ilgili görsel ve skor bilgisi güncellenmektedir.
- **Dosya Tabanlı Skor Takibi:** Oyun sonunda kesilen ve kaçırılan karpuz sayıları bir `.txt` dosyasına yazılmakta, önceki skorlarla karşılaştırılarak maksimum skor bilgisi saklanmaktadır.
- **Koordinat Tabanlı Nesne Yerleşimi:** Nesneler, dışarıdan alınan bir koordinat dosyasına göre belirli pozisyonlara yerleştirilmekte ve bu sayede daha kontrollü bir oyun alanı oluşturulmaktadır.
- **Modüler Yapı:** `Dialog` ve `resim` gibi ayrı sınıflarla hem oyun mantığı hem de görsellik birbirinden ayrılarak daha okunabilir ve genişletilebilir bir yapı elde edilmiştir.

## Features

- **GUI Development with Qt Framework:** The game interface is developed using QWidget-based architecture, featuring dynamic buttons and interactive UI components.
- **Timer-Based Game Mechanics:** Leveraging Qt's `QTimer` class, fruits (watermelons) are spawned at timed intervals with randomized positions for dynamic gameplay.
- **Click Detection and Cutting Logic:** Using mouse click events on `QPushButton` elements, the system determines whether a fruit has been sliced and updates the corresponding icon and score accordingly.
- **Score Tracking via File I/O:** At the end of each session, the number of sliced and missed fruits is written to a `.txt` file and compared against previous scores to track the maximum score.
- **Coordinate-Based Object Placement:** Fruit positions are determined using an external coordinate file, allowing for controlled and repeatable object placement within the game area.
- **Modular Architecture:** Core functionalities such as game logic and rendering are separated into different classes (e.g., `Dialog`, `resim`), ensuring better readability and maintainability.
