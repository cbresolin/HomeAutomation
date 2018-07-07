FROM arm32v7/debian:stretch-slim

MAINTAINER christophe.bresolin@gmail.com

# Environment variables

# Check nginx_default file to ensure
# nginx home is correct (root property)
ENV WEBSERVER_HOME /var/www/html

# Check Jeedom github project for exact branch names
ENV JEEDOM_BRANCH stable

# Dependancies
RUN apt-get update && \
    apt-get -y dist-upgrade && \
    apt-get install -y \
    apt-utils \
    ca-certificates \
    cron \
    curl \
    nano \
    mysql-client \
    nginx \
    ntp \
    php7.0 \
    php7.0-common \
    php7.0-cli \
    php7.0-curl \
    php7.0-fpm \
    php7.0-gd \
    php7.0-imap \
    php7.0-json \
    php7.0-mbstring \
    php7.0-mysql \
    php7.0-opcache \
    php7.0-xml \
    sudo \
    supervisor \
    unzip \
    wget && \
    apt-get autoremove --purge && \
    rm -rf /var/lib/apt/lists/*

# NGINX Default Configuration
RUN rm /etc/nginx/sites-available/default
COPY nginx_default /etc/nginx/sites-available/default

# See https://www.digitalocean.com/community/tutorials/how-to-create-an-ssl-certificate-on-nginx-for-ubuntu-14-04
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 3650 -newkey rsa:4096 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -subj "/C=FR/ST=France/L=Toulouse/O=./OU=./CN=jeedom.cbresolin.ovh/emailAddress=christophe.bresolin@gmail.com" && \
    chmod 400 /etc/nginx/ssl/nginx.key

# PHP Configuration
RUN sed -i 's/max_execution_time = 30/max_execution_time = 800/g' /etc/php/7.0/fpm/php.ini && \
    sed -i 's/upload_max_filesize = 2M/upload_max_filesize = 1G/g' /etc/php/7.0/fpm/php.ini && \
    sed -i 's/post_max_size = 8M/post_max_size = 1G/g' /etc/php/7.0/fpm/php.ini

# Install Jeedom
RUN mkdir -p $WEBSERVER_HOME/log && \
    wget https://github.com/jeedom/core/archive/$JEEDOM_BRANCH.zip -O /tmp/jeedom.zip && \
    unzip -q /tmp/jeedom.zip -d /root/ && \
    cp -R /root/core-*/* $WEBSERVER_HOME && \
    cp -R /root/core-*/.htaccess $WEBSERVER_HOME && \
    rm -rf /root/core-* && \
    sed -i 's/127.0.0.1;192.168.*.*/127.0.0.1;192.168.*.*;172.17.*.*\"/' $WEBSERVER_HOME/core/config/default.config.ini

# Sudo access rules
RUN echo "www-data ALL=(ALL) NOPASSWD: ALL" | (EDITOR="tee -a" visudo)
RUN chmod 775 -R $WEBSERVER_HOME && \
    chown -R www-data:www-data $WEBSERVER_HOME && \
    usermod -a -G dialout,tty www-data

# Clean-up /tmp
RUN rm -rf /tmp/*

# Supervisor
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# Add crontab when container is launched (to avoid the HARDLINKS issue)
COPY ./add_crontab /etc/supervisor/
RUN chmod +x /etc/supervisor/add_crontab

# Create log dir in case it is launched using tmpfs
COPY ./start_supervisord /
RUN chmod +x /start_supervisord

CMD ["/start_supervisord"]
