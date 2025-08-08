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

    options {
        timestamps()
        ansiColor('xterm')
        buildDiscarder(logRotator(numToKeepStr: '20'))
        disableConcurrentBuilds()
    }
    stages {
       
        stage('Build') {
            steps {
                sh 'make all'
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