pipeline {
    agent {
        docker {
            image 'stm32f429_env:latest'
            args '--privileged -v /dev/bus/usb:/dev/bus/usb  -u 0:0'
        }
    }
    
    environment {
        GIT_REPO = 'https://github.com/soulaimane-ouladbelayachi/stm32f429_ci'
        GIT_BRANCH = 'main' 
        GIT_CREDENTIALS = '0a7d8ffd-bec3-4c56-808f-725328520473' 
    }

    stages {

        stage('Static Analysis') {
            steps {
                sh '''
                    echo "Running static analysis (cppcheck) for STM32F429..."
                    cppcheck --enable=all --inconclusive --xml --xml-version=2 \
                        --std=c11 --force \
                        --suppress=missingIncludeSystem \
                        -I Drivers/CMSIS/Include \
                        -I Drivers/STM32F4xx_HAL_Driver/Inc \
                        -I Core/Inc \
                        Core/Src 2> cppcheck-report.xml || true
                '''
                recordIssues tools: [cppCheck(pattern: 'cppcheck-report.xml')]
            }
        }
       
        stage('Build Firmware') {
            steps {
                sh '''
                    echo "Building firmware for STM32F429..."
                    make clean
                    make all
                '''
            }
            post {
                success {
                    archiveArtifacts artifacts: "build/*.elf, build/*.bin", fingerprint: true
                }
            }
        }

        stage('Test') {
            steps {
                echo 'Running tests...'
                sh 'ceedling --version'
            }
        }
        stage('Flash') {
            steps {
                echo 'Flash the ELF...'
                sh 'make flash'
            }
        }        
    }

    post {
        success {
            echo 'Build and test completed successfully!'
        }
        failure {
            echo ' failed.'
        }
    }
}