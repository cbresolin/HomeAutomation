FROM armhf/debian

MAINTAINER christophe.bresolin@gmail.com

# Environment variables
ENV JEEDOM_VERSION stablev3
ENV WEBSERVER_HOME /usr/share/nginx/www/jeedom

# Dependancies
RUN apt-get update && apt-get install -y \
    apt-utils \
    ca-certificates \
    cron \
    curl \
    dialog \
    libterm-readline-perl-perl \
    mysql-client \
    nginx-common \
    nginx-full \
    ntp \
    php5-cli \
    php5-common \
    php5-curl \
    php5-fpm \
    php5-gd \
    php5-json \
    php5-mysql \
    sudo \
    supervisor \
    unzip \
    wget && \
    apt-get autoremove --purge && \
    rm -rf /var/lib/apt/lists/*

# PHP Configuration
RUN sed -i 's/max_execution_time = 30/max_execution_time = 600/g' /etc/php5/fpm/php.ini && \
    sed -i 's/upload_max_filesize = 2M/upload_max_filesize = 1G/g' /etc/php5/fpm/php.ini && \
    sed -i 's/post_max_size = 8M/post_max_size = 1G/g' /etc/php5/fpm/php.ini && \
    sed -i 's/expose_php = On/expose_php = Off/g' /etc/php5/fpm/php.ini && \
    sed -i 's/pm.max_children = 5/pm.max_children = 20/g' /etc/php5/fpm/pool.d/www.conf

# NGINX Jeedom configuration (ssl + certificates)
# See http://nginx.org/en/docs/http/configuring_https_servers.html
RUN rm /etc/nginx/sites-available/default && \
    rm /etc/nginx/sites-enabled/default
COPY nginx_default /etc/nginx/sites-available/default
RUN ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default

# Sudo access rules
RUN echo "www-data ALL=(ALL) NOPASSWD: ALL" | (EDITOR="tee -a" visudo)

# Jeedom install
RUN mkdir -p $WEBSERVER_HOME && \
    mkdir -p $WEBSERVER_HOME/log && \
    wget https://github.com/jeedom/core/archive/$JEEDOM_VERSION.zip -O /tmp/jeedom.zip && \
    unzip -q /tmp/jeedom.zip -d /root/ && \
    cp -R /root/core-*/* $WEBSERVER_HOME/ && \
    cp -R /root/core-*/.htaccess $WEBSERVER_HOME/ && \
    rm -rf /root/core-*
RUN sed -i 's/,127.0.0.1/,127.0.0.1,172.17.*.*/' $WEBSERVER_HOME/core/config/default.config.ini

# Openzwave plugin install
# RUN wget https://github.com/jeedom/plugin-openzwave/archive/master.zip -O /tmp/plugin-openzwave-master.zip && \
#    unzip -q /tmp/plugin-openzwave-master.zip -d /root/ && \
#    chmod +x /root/plugin-openzwave-master/resources/install.sh && \
#    /root/plugin-openzwave-master/resources/install.sh && \
#    rm -rf /root/plugin-openzwave-master
# RUN mkdir -p $WEBSERVER_HOME/plugins/openzwave/data

RUN chmod 775 -R $WEBSERVER_HOME && \
    chown -R www-data:www-data $WEBSERVER_HOME && \
    usermod -a -G dialout,tty www-data

# Clean-up
RUN rm -rf /tmp/*

# SSL - https://www.digitalocean.com/community/tutorials/how-to-create-an-ssl-certificate-on-nginx-for-ubuntu-14-04
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -subj "/C=FR/ST=France/L=Nice/O=Home/OU=Home/CN=jeedom.com"

# Supervisor
RUN echo "daemon off;" >> /etc/nginx/nginx.conf
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# Add crontab when container is launched (to avoid the HARDLINKS issue)
COPY ./add_crontab /etc/supervisord/
RUN chmod +x /etc/supervisord/add_crontab

# Create log dir in case it is launched using tmpfs
COPY ./start_supervisord /
RUN chmod +x /start_supervisord

CMD ["/start_supervisord"]
