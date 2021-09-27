import React from 'react';
import PropTypes from 'prop-types';

import './WeatherDisplay.css';
import './owfont-regular.css'
import './WeatherReport.css';

export default class WeatherDisplay extends React.Component {
    static propTypes = {
        masking: PropTypes.bool,
        group: PropTypes.string,
        description: PropTypes.string,
        temp: PropTypes.number,
        unit: PropTypes.string
    };

    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className={`WeatherReport ${this.props.masking} ? 'masking' : ''}`}>
				<table><tbody>
				<tr>
					<td>
						<span>{this.props.date[this.props.id]}: </span>
					</td>
					<td>
						<h5 className='temp'>
							<span className='display-5'>{this.props.forecast[this.props.id].temp.toFixed(0)}&ordm;</span>
							&nbsp;{(this.props.unit === 'metric')
								? 'C'
								: 'F'}
						</h5>
					</td>
					<td>
						<i className={`owf owf-2x owf-${this.props.forecast[this.props.id].code}`}></i>
					</td>
				</tr>
				</tbody></table>
            </div>
        );
    }
}
