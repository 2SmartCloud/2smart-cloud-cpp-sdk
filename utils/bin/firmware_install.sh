#!/usr/bin/env bash
FOLDER=$PWD

help() {
    cat <<HELP
Simplify docker firmware builder commands

Usage: ./firmware_install.sh COMMAND [FLAGS]

Commands:
    simple_write                                                    build and write firmware without docker
    write [-d|--device DEVICE]                                      write build to device
    erase [-d|--device DEVICE]                                      erase flash from device
    build [-d|--device DEVICE]                                      build firmware
    upload [-d|--device DEVICE]                                     upload only firmware on device
    uploadfs [-d|--device DEVICE]                                   upload static files on device
Flags:
    -d|--device DEVICE (required)         device which appear after connectig microcontroller to your PC
    -f|--folder FOLDER                    folder with your firmware
HELP
}

uploadfs() {
    if [ -z $DEVICE ] 
        then
        echo "MISSNG ARGUMENT: -d|--device DEVICE is required"
        IS_ARGS_MISSING=1
    fi

    check_is_missing_args


    esptool_command="docker run --rm \
        -v "${FOLDER}":/workspace \
        -u `id -u $USER`:`id -g $USER` \
        --device=$DEVICE \
        -it sglahn/platformio-core:latest \
        run -t uploadfs"
    printf "firmware installation running \n"
    eval $esptool_command
}

simple_write() {
    esptool_command="pio run -t uploadfs && pio run -t upload"
    printf "firmware installation running \n"
    eval $esptool_command
}


write() {
    if [ -z $DEVICE ] 
        then
        echo "MISSNG ARGUMENT: -d|--device DEVICE is required"
        IS_ARGS_MISSING=1
    fi

    check_is_missing_args


    esptool_command="docker run --rm \
        -v "${FOLDER}":/workspace \
        -u `id -u $USER`:`id -g $USER` \
        --device=$DEVICE \
        -it sglahn/platformio-core:latest \
        run -t uploadfs && upload"
    printf "firmware installation running \n"
    eval $esptool_command
}

upload() {
    if [ -z $DEVICE ] 
        then
        echo "MISSNG ARGUMENT: -d|--device DEVICE is required"
        IS_ARGS_MISSING=1
    fi

    check_is_missing_args


    esptool_command="docker run --rm \
        -v "${FOLDER}":/workspace \
        -u `id -u $USER`:`id -g $USER` \
        --device=$DEVICE \
        -it sglahn/platformio-core:latest \
        run -t upload"
    printf "firmware installation running \n"
    eval $esptool_command
}

build() {
    check_is_missing_args

    esptool_command="docker run --rm \
        -v "${FOLDER}":/workspace \
        -u `id -u $USER`:`id -g $USER` \
        --device=$DEVICE \
        -it sglahn/platformio-core:latest \
        run"

    printf "running esptool command:\n$esptool_command\n"
    eval $esptool_command
}

erase() {
    check_is_missing_args

    esptool_command="docker run --rm \
        -v "${FOLDER}":/workspace \
        -u `id -u $USER`:`id -g $USER` \
        --device=$DEVICE \
        -it sglahn/platformio-core:latest \
        run -t erase"

    printf "running esptool command:\n$esptool_command\n"
    eval $esptool_command
}


check_is_missing_args() {
    if [ ! -z $IS_ARGS_MISSING ]
        then
        help
        exit 1
    fi
}

if [[ $# == 0 ]]; then
    help
    exit 1
fi

ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        -d|--device)
            read -ra val <<< "$2"
            if [ -z $2 ]; then help && exit 1; fi

            DEVICE=$2
            shift 2
            ;;
        -f|--folder)
            read -ra val <<< "$2"
            if [ -z $2 ]; then help && exit 1; fi

            FOLDER=$2
            shift 2
            ;;
        write|erase|build|uploadfs|upload|simple_write)
            COMMAND=$1
            shift
            ;;
        *)
            printf "\e[31mcommand '%s' is not supported\e[0m\n" "$1"
            help
            exit 1
            ;;

    esac
done

printf -v args "%s" "${ARGS[@]}"

"$COMMAND" "$args"
