#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QSet>
#include <QVersionNumber>

class Action{
public:
    QString capability;
    QString device;
    QString status;
    QString error_message;
};

class Battery{
public:
    Battery();
    Battery(QString stat, int lev);
    QString status = "BATTERY_UNAVAILABLE";
    int level = 0;
};

class EqualizerPreset{
public:
    QString name;
    QList<double> values;
};

class Equalizer{
public:
    Equalizer();
    Equalizer(int bands, int baseline, double step, int min, int max);

    int bands_number = 0;
    int band_baseline = 0;
    double band_step = 0;
    int band_min = 0;
    int band_max = 0;
};

class Device
{
public:
    Device();
    Device(const QJsonObject& jsonObj, QString jsonData);

    //Status
    bool connected = false;

    //Basic info
    QString device;
    QString vendor;
    QString product;
    QString id_vendor;
    QString id_product;
    QSet<QString> capabilities;

    //Info to get from json and display
    Battery battery;
    int chatmix = 65;
    QList<EqualizerPreset> presets_list;
    Equalizer equalizer;
    bool notification_sound=false;

    //Info to set with gui and to save
    int lights=-1;
    int sidetone=-1;
    int voice_prompts=-1;
    int inactive_time=-1;
    int equalizer_preset=-1;
    QList<int> equalizer_curve;
    int volume_limiter=-1;
    int rotate_to_mute=-1;
    int mic_mute_led_brightness=-1;
    int mic_volume=-1;
    int bt_when_powered_on=-1;
    int bt_call_volume=-1;

    bool operator!=(const Device& d) const;
    bool operator==(const Device &d) const;
    bool operator==(const Device* d) const;

    void updateDevice(const Device* new_device);
    void updateDevice(const QList<Device*>& new_device_list);

    QJsonObject toJson() const;
    static Device fromJson(const QJsonObject& json);
};

QString sendCommand(const QStringList& args_list);
Action sendAction(const QStringList& args_list);

QVersionNumber getHCVersion();

QList<Device*> getDevices();
QList<Device*> mergeDevices(QList<Device*> connectedDevices, const QList<Device*>& savedDevices);
QList<Device*> getSavedDevices(const QString& file_name);
QList<Device*> getConnectedDevices();

void serializeDevices(const QList<Device*>& devices, const QString& filename);
QList<Device*> deserializeDevices(const QString& filename);

#endif // DEVICE_H
