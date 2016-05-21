<wifi_network>
    <div class="input-group">
        <input name="wifi_network" type="text" class="form-control"/>
        <div class="input-group-btn">
            <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown">
                <div class="dropdown-button">
                    <div name="spinner" class="spinner">
                        <div class="double-bounce1"></div>
                        <div class="double-bounce2"></div>
                    </div>
                    <div name="caret" class="dropdown-caret"></div>
                </div>
            </button>
            <ul class="dropdown-menu dropdown-menu-right">
                <li each={ wifi_networks }>
                    <a href="#" onclick={ parent.select_wifi }>
                        <i if="{ rssi }" class="glyphicon" style="width:24px">
                            <ul class="signal-bars bars-{ rssi }">
                                <li class="first-bar bar">
                                    <div></div>
                                </li>
                                <li class="second-bar bar">
                                    <div></div>
                                </li>
                                <li class="third-bar bar">
                                    <div></div>
                                </li>
                                <li class="fourth-bar bar">
                                    <div></div>
                                </li>
                            </ul>
                        </i>
                        <i if="{ encryption }" class="icon-lock"></i>
                        <i if="{ !encryption }" class="icon-spacer"></i>
                        { ssid }
                    </a>
                </li>
            </ul>
        </div>
    </div>
    <script>
        var that = this;
        this.wifi_networks = [
            {
                name: "Scanning..."
            }
        ];

        this.on('mount', function () {
            var dropdown = this.root.querySelector('[data-toggle=dropdown]');
            new Dropdown(dropdown);
        })

        this.on('update', function () {
            that.wifi_network.value = opts.settings.wifi_network;
        })

        select_wifi(event) {
            var item = event.item
            if (item.rssi)
                opts.settings.wifi_network = item.ssid;
            }

        hide_spinner() {
            this.spinner.style.opacity = 0;
            this.caret.style.opacity = 1;
        }

        fetch('/wifi_networks').then(function (response) {
            return response.json()
        }).then(function (json) {
            that.hide_spinner();
            that.wifi_networks = json.sort(function (a, b) {
                return b.rssi - a.rssi;
            })
            that.wifi_networks.forEach(function (entry) {
                var strength = 1;
                if (entry.rssi > -70)
                  strength = 2;
                if (entry.rssi > -60)
                  strength = 3;
                if (entry.rssi > -50)
                  strength = 4;
                entry.rssi = strength;
                entry.encryption = (entry.encryption != "None");
            });
            that.update();
        }).catch(function (ex) {
            that.hide_spinner();
            console.log('wifi networks parsing failed', ex)
        })
    </script>
</wifi_network>
<connect>
    <div class="container">
        <form class="form form-connect" role="form" onsubmit={ updateSettings }>
            <h1 class="form-connect-heading">Please connect me to your WiFi</h1>
            <br/>
            <div class="form-group">
                <label for="name">My name is</label>
                <input name="name" type="text" class="form-control"/>
            </div>
            <div class="form-group">
                <label for="network">WiFi network</label>
                <wifi_network settings={ settings }></wifi_network>
            </div>
            <div class="form-group">
                <label for="password">WiFi password</label>
                <input id="password" type="password" class="form-control"/>
            </div>
            <br/>
            <div class="form-group">
                <button if="{ settings.connected }" class="btn btn-lg btn-danger btn-block" type="submit">Disconnect</button>
                <button if="{ !settings.connected }" class="btn btn-lg btn-primary btn-block" type="submit">Connect</button>
            </div>
        </form>
    </div>
    <script>
        this.settings = {
            wifi_network: ''
        };
        var that = this;

        updateSettings(e) {
            var settings = {
              name: that.name.value,
              wifi_network: that.settings.wifi_network,
              wifi_password: that.name.password,
              connected: !that.settings.connected
            }
            fetch('/settings', {
                method: 'PUT',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(settings)
            }).then(function (response) {
                that.refetchSettings();
            });
        };

        refetchSettings() {
            fetch('/settings').then(function (response) {
                return response.json()
            }).then(function (json) {
                that.settings = json;
                that.name.value = json.name;
                that.update();
            }).catch(function (ex) {
                console.log('settings parsing failed', ex)
            });
        };

        this.refetchSettings();
    </script>
</connect>
