//
// Created by Michał on 06.12.2023.
//

#ifndef LAB6_NODES_HPP
#define LAB6_NODES_HPP

#include "types.hpp"
#include "helpers.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "config.hpp"
#include <map>
#include <optional>
#include <memory>
#include <utility>

enum ReceiverType{
    WORKER, STOREHOUSE
};

class IPackageReceiver {
public:
    virtual void receive_package(Package&& p) = 0;

    virtual ElementID get_id() const = 0;

    virtual IPackageStockpile::const_iterator cbegin() const = 0;

    virtual IPackageStockpile::const_iterator cend() const = 0;

    virtual IPackageStockpile::const_iterator begin() const = 0;

    virtual IPackageStockpile::const_iterator end() const = 0;


    virtual ReceiverType get_receiver_type() const = 0;

    virtual  ~IPackageReceiver() = default;
};


class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(std::move(pg)) {}

    void add_receiver(IPackageReceiver* r);

    void remove_receiver(IPackageReceiver* r);

    IPackageReceiver* choose_receiver();

    const preferences_t& get_preferences() const { return preferences_; }

    const_iterator cbegin() const { return preferences_.cbegin(); }

    const_iterator cend() const { return preferences_.cend(); }

    const_iterator begin() const { return preferences_.cbegin(); }

    const_iterator end() const { return preferences_.cend(); }

    ~ReceiverPreferences() = default;
private:
    preferences_t preferences_;
    ProbabilityGenerator pg_;
};

class PackageSender {
public:
    ReceiverPreferences receiver_preferences_;

    PackageSender() = default;

    PackageSender(PackageSender&& sender) = default;

    void send_package();

    const std::optional<Package>& get_sending_buffer() const { return bufor_; }

    ~PackageSender() = default;
protected:
    void push_package(Package&& package);

private:
    std::optional<Package> bufor_ = std::nullopt;
};

class Ramp : public PackageSender {
public:
    explicit Ramp(ElementID id, TimeOffset di) : PackageSender(), id_(id), di_(di) {}

    Ramp(Ramp&& ramp) = default;

    Ramp(const Ramp &ramp);

    Ramp& operator=(const Ramp &ramp) noexcept;

    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() const { return di_;}

    ElementID get_id() const { return id_; }

    ~Ramp() = default;
private:
    ElementID id_;
    TimeOffset di_;
    std::optional<Package> bufor_ = std::nullopt;
};

class Worker : public PackageSender, public IPackageReceiver{
public:
    explicit Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender(), id_(id), pd_(pd), q_(std::move(q)) {}

    void do_work(Time t);

    Worker() = default;

    Worker(Worker&& worker) = default;

    Worker(const Worker &worker);

    Worker& operator=(const Worker &worker) noexcept;

    TimeOffset  get_processing_duration() const { return pd_; }

    Time get_package_processing_start_time() const { return t_; }

    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); }

    IPackageStockpile::const_iterator begin() const override { return q_->begin(); }

    IPackageStockpile::const_iterator cend() const override { return q_->cend(); }

    IPackageStockpile::const_iterator end() const override { return q_->end();  }

    void receive_package(Package&& p) override;

    ElementID get_id() const override { return id_; }


    ReceiverType get_receiver_type() const override { return receiverType_; }


    IPackageQueue* get_queue() const { return q_.get(); }

    ~Worker() = default;
private:
    ReceiverType receiverType_ = WORKER;
    ElementID id_;
    TimeOffset pd_;
    Time t_;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> bufor_ = std::nullopt;
};

class Storehouse : public IPackageReceiver{
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) : id_(id), d_(std::move(d)) {}

    Storehouse(Storehouse&& storehouse) = default;

    Storehouse(const Storehouse &storehouse) : id_(storehouse.get_id()) {}

    Storehouse& operator=(const Storehouse &storehouse) noexcept { id_ = storehouse.get_id(); return *this;}

    ElementID get_id() const override { return id_; }

    void receive_package(Package&& p) override;

    IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); }

    IPackageStockpile::const_iterator begin() const override { return d_->begin(); }

    IPackageStockpile::const_iterator cend() const override { return d_->cend(); }

    IPackageStockpile::const_iterator end() const override { return d_->end();  }


    ReceiverType get_receiver_type() const override { return receiverType_; }


    ~Storehouse() = default;

private:
    ReceiverType receiverType_ = STOREHOUSE;
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};

#endif //LAB6_NODES_HPP
