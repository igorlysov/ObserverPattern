#include "Observer.h"

int main() {
    /* Main в этом случае - Клиент.
     * Объявляем нашего Издателя - некоторый музыкальный сервис */
    Spotify spotifyService;
    /* Наполняем наш сервис различными подписчиками */
    std::cout << "New subscribers!" << std::endl;
    FreeSubscriber freeSubscriber(&spotifyService, "IgorL");
    PremiumSubscriber premiumSubscriber(&spotifyService, "MatveyA", 31, 50.0);
    ProSubscriber proSubscriber(&spotifyService, "RomanN", 31, 76.5);
    /* Посмотим на данные наших пользователей */
    std::cout << "Subscribers' info:" << std::endl;
    freeSubscriber.printInfo();
    premiumSubscriber.printInfo();
    proSubscriber.printInfo();
    /* Можем обновить данные пользователя -  изменить количество дней
     * до продления подписки или данные о кошельке (допустим, что
     * щедрый Spotify решил начислить всем 100). */
    std::cout << "Some updates:" << std::endl;
    spotifyService.setInfo(29, 100);
    /* Посмотрим на данные после обновления */
    std::cout << "Subscribers' new info:" << std::endl;
    freeSubscriber.printInfo();
    premiumSubscriber.printInfo();
    proSubscriber.printInfo();
    /* Пусть некоторые пользователи ушли с нашего сервиса */
    std::cout << "Some subscribes has gone :(" << std::endl;
    premiumSubscriber.unsubscribe();
    return 0;
}
