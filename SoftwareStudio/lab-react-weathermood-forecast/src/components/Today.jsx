import React from 'react';
import PropTypes from 'prop-types';
import {
    BrowserRouter as Router,
    Route,
    Link
} from 'react-router-dom'
import {
    Collapse,
    Navbar,
    NavbarToggler,
    NavbarBrand,
    Nav,
    NavItem,
    NavLink
} from 'reactstrap';

import WeatherDisplay from 'components/WeatherDisplay.jsx';
import WeatherForm from 'components/WeatherForm.jsx';
import WeatherReport from 'components/WeatherReport.jsx';
import { getWeather, getForecast } from 'api/open-weather-map.js';

import './weather.css';

export default class Today extends React.Component {
    static propTypes = {
        masking: PropTypes.bool,
        group: PropTypes.string,
        description: PropTypes.string,
        temp: PropTypes.number,
        unit: PropTypes.string
    };

    static getInitWeatherState() {
        return {
            city: 'na',
            code: -1,
            group: 'na',
            description: 'N/A',
            temp: NaN,
			forecast: [
				{ temp: NaN }, 
				{ temp: NaN }, 
				{ temp: NaN }, 
				{ temp: NaN }
			]
        };
    }

    constructor(props) {
        super(props);

        this.state = {
            ...Today.getInitWeatherState(),
            loading: true,
            masking: true,
			date: this.getDates(props.description)
        };

        this.handleFormQuery = this.handleFormQuery.bind(this);
    }
	
	getDates(today) {
		let mapping = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']
		var i = new Date().getDay();
		return [
			mapping[(i + 1) % 7], 
			mapping[(i + 2) % 7],
			mapping[(i + 3) % 7],
			mapping[(i + 4) % 7]
		]
	}
	
    componentDidMount() {
        this.getWeather('Hsinchu', 'metric');
    }

    componentWillUnmount() {
        if (this.state.loading) {
            cancelWeather();
        }
    }

    render() {
		let _1 = {...this.state}, _2 = {...this.state}, _3 = {...this.state}, _4 = {...this.state};
		_1.id = 0;
		_2.id = 1;
		_3.id = 2;
		_4.id = 3;
		
		return (
            <div className={`today weather-bg ${this.state.group}`}>
                <div className={`mask ${this.state.masking ? 'masking' : ''}`}>
                    <WeatherForm city={this.state.city} unit={this.props.unit} onQuery={this.handleFormQuery}/>
					<WeatherDisplay {...this.state} />
		    		<table style={ {"margin": "auto"} }><tbody>
					<tr>
						<td>
							<WeatherReport {..._1} />
						</td>
						<td>
							<WeatherReport {..._2} />
						</td>
						<td>
							<WeatherReport {..._3} />
						</td>
						<td>
							<WeatherReport {..._4} />
						</td>
					</tr>
					</tbody></table>
                </div>
            </div>
        );
    }

    getWeather(city, unit) {
        this.setState({
            loading: true,
            masking: true,
            city: city // set city state immediately to prevent input text (in WeatherForm) from blinking;
        }, () => { // called back after setState completes
            getWeather(city, unit).then(weather => {
                this.setState({
                    ...weather,
                    loading: false
                }, () => this.notifyUnitChange(unit));
            }).catch(err => {
                console.error('Error getting weather', err);

                this.setState({
                    ...Today.getInitWeatherState(unit),
                    loading: false
                }, () => this.notifyUnitChange(unit));
            });

            getForecast(city, unit).then(forecast => {
                this.setState({
                    forecast: forecast,
                    loading: false
                }, () => this.notifyUnitChange(unit));
            }).catch(err => {
                console.error('Error getting weather', err);

                this.setState({
                    ...Today.getInitWeatherState(unit),
                    loading: false
                }, () => this.notifyUnitChange(unit));
            })		
        });

        setTimeout(() => {
            this.setState({
                masking: false
            });
        }, 600);
    }

    handleFormQuery(city, unit) {
        this.getWeather(city, unit);
    }

    notifyUnitChange(unit) {
        if (this.props.units !== unit) {
            this.props.onUnitChange(unit);
        }
    }
}
