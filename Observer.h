//
// Created by мвидео on 29.11.2021.
//

#ifndef OBSERVER_OBSERVER_H
#define OBSERVER_OBSERVER_H

#include <iostream>
#include <string>
#include <list>

/*** ИНТЕРФЕЙС ПОДПИСЧИКА ***/
class ISubscriber {
public:
    virtual void updateInfo(int days, double wallet) = 0;
    virtual void printInfo() = 0;
    virtual std::string getLicense() = 0;
};

/*** ИНТЕРФЕЙС ИЗДАТЕЛЯ ***/
class IPublisher {
public:
    virtual void registerSubscriber(ISubscriber &subscriber) = 0;
    virtual void deleteSubscriber(ISubscriber &subscriber) = 0;
    virtual void notifySubscriber() = 0;
    virtual void setInfo(int days, double wallet) = 0;
};

/* Пусть у нас есть некоторый музыкальный сервис,
 * который поддерживает три версии подписки:
 * 1) Free
 * 2) Premium
 * 3) PRO */

/*** КОНКРЕТНЫЙ ПОДПИСЧИК - PRO ПОДПИСКА ***/
class ProSubscriber : public ISubscriber {
private:
    IPublisher* publisher_;
    std::string name_;
    int daysToPayment_;
    double wallet_;
public:
    ProSubscriber(IPublisher* musicService, std::string name,
                  int days=31, double wallet=0.0) : name_(name), daysToPayment_(days), wallet_(wallet) {
            this->subscribe(musicService);
        }
    void updateInfo(int days, double wallet) override {
        daysToPayment_ = days;
        wallet_ = wallet;
        std::cout << "PRO license is updated!" << std::endl;
    }
    void printInfo() override {
        std::cout << "Name: " << this->name_ << std::endl <<
                     "Days to new payment: " << this->daysToPayment_ << std::endl <<
                     "Wallet: " << this->wallet_ << std::endl << std::endl;
    }
    void subscribe(IPublisher* musicService) {
        publisher_ = musicService;
        publisher_->registerSubscriber(*this);
        std::cout << "I'm a new PRO subscriber. Hi!" << std::endl << std::endl;
    }
    void unsubscribe() {
        publisher_->deleteSubscriber(*this);
        std::cout << "I'm not a PRO subscriber anymore. Goodbye!" << std::endl << std::endl;
    }
    std::string getLicense() override {
        return "PRO license";
    }

};

/*** КОНКРЕТНЫЙ ПОДПИСЧИК - PREMIUM ПОДПИСКА ***/
class PremiumSubscriber : public ISubscriber {
private:
    IPublisher* publisher_;
    std::string name_;
    int daysToPayment_;
    double wallet_;
public:
    PremiumSubscriber(IPublisher* musicService, std::string name,
                      int days=31, double wallet=0.0) : name_(name), daysToPayment_(days), wallet_(wallet) {
        this->subscribe(musicService);
    }
    void updateInfo(int days, double wallet) override {
        daysToPayment_ = days;
        wallet_ = wallet;
        std::cout << "PREMIUM license is updated!" << std::endl;
    }
    void printInfo() override {
        std::cout << "Name: " << this->name_ << std::endl <<
                  "Days to new payment: " << this->daysToPayment_ << std::endl <<
                  "Wallet: " << this->wallet_ << std::endl << std::endl;
    }
    void subscribe(IPublisher* musicService) {
        publisher_ = musicService;
        publisher_->registerSubscriber(*this);
        std::cout << "I'm a new PREMIUM subscriber. Hi!" << std::endl << std::endl;
    }
    void unsubscribe() {
        publisher_->deleteSubscriber(*this);
        std::cout << "I'm not a PREMIUM subscriber anymore. Goodbye!" << std::endl << std::endl;
    }
    std::string getLicense() override {
        return "PREMIUM license";
    }
};

/*** КОНКРЕТНЫЙ ПОДПИСЧИК - FREE ПОДПИСКА ***/
class FreeSubscriber : public ISubscriber {
private:
    IPublisher* publisher_;
    std::string name_;
public:
    FreeSubscriber(IPublisher* musicService, std::string name) : name_(name) {
        this->subscribe(musicService);
    }
    void updateInfo(int days, double wallet) override {
        std::cout << "FREE license is updated!" << std::endl;
    }
    void printInfo() override {
        std::cout << "Name: " << this->name_ << std::endl << std::endl;
    }
    void subscribe(IPublisher* musicService) {
        publisher_ = musicService;
        publisher_->registerSubscriber(*this);
        std::cout << "I'm a new FREE subscriber. Hi!" << std::endl << std::endl;
    }
    void unsubscribe() {
        publisher_->deleteSubscriber(*this);
        std::cout << "I'm not a FREE subscriber anymore. Goodbye!" << std::endl << std::endl;
    }
    std::string getLicense() override {
        return "FREE license";
    }
};

/*** КОНКРЕТНЫЙ ИЗДАТЕЛЬ - МУЗЫКАЛЬНЫЙ СЕРВИС ***/
class Spotify : public IPublisher {
private:
    std::list<ISubscriber*> subscribers_;
    int daysToPayment_;
    double wallet_;
public:
    Spotify() = default;
    ~Spotify() {
        subscribers_.clear();
    }
    void registerSubscriber(ISubscriber &subscriber) override {
        std::cout << "Subscriber registered" << std::endl;
        subscribers_.push_back(&subscriber);
    }
    void deleteSubscriber(ISubscriber &subscriber) override {
        std::cout << "Subscriber deleted" << std::endl;
        subscribers_.remove(&subscriber);
    }
    void notifySubscriber() override {
        for (auto &subscriber : subscribers_) {
            std::cout << "License type: " << subscriber->getLicense() << std::endl;
            subscriber->updateInfo(daysToPayment_, wallet_);
            std::cout << "Subscriber notified" << std::endl << std::endl;
        }
    }
    void setInfo(int days, double wallet) override {
        daysToPayment_ = days;
        wallet_ = wallet;
        notifySubscriber();
    }
};


#endif //OBSERVER_OBSERVER_H
