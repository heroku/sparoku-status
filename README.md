# Sparoku Status

This is a firmware for Spark Core with [Button](https://www.spark.io/button) to make the device ready to work with [Sparoku Drains](https://github.com/heroku/sparoku-drain).

It relies on the [SparkButton](https://github.com/jenesaisdiq/SparkButton) library to control the lights on the button shield.


## Setup

First connect and claim your Spark Core device following [their guide](http://docs.spark.io/start/).

Then to compile and flash the device with this firmware:

```bash
# so we know which device to flash
$ export SPARK_DEVICE=$YOUR_SPARK_DEVICE_NAME

# compile and flash it
$ rake
```

## Testing locally

Before hooking this up to a drain, you can test this locally by triggering the exposed functions, like:

```bash
$ rake simulate
```

If everything is working you should see LEDs light up on your Spark Button.
