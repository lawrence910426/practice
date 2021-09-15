import React from 'react';
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
    NavLink,
    DropdownToggle,
    DropdownMenu,
    DropdownItem,
    UncontrolledDropdown
} from 'reactstrap';
import { instanceOf } from 'prop-types';
import { withCookies, Cookies } from 'react-cookie';

import Today from 'components/Today.jsx';
import Forecast from 'components/Forecast.jsx';

import './Main.css';

class Main extends React.Component {
    static propTypes = {
        cookies: instanceOf(Cookies).isRequired
    };

    constructor(props) {
        super(props);

        const { cookies } = props;
        this.state = {
            unit: 'metric',
            city: 'na',
            navbarToggle: false,
            favoriteCities: cookies.get('cities')? cookies.get('cities').split(';') : []
        };
		this.props = props;
        this.handleNavbarToggle = this.handleNavbarToggle.bind(this);
        this.handleFormQuery = this.handleFormQuery.bind(this);
        this.setFavoriteCities = this.setFavoriteCities.bind(this);
        this.clearFavoriteCities = this.clearFavoriteCities.bind(this);
    }
    // TODO
    render() {
		let cities = this.state.favoriteCities.map(item => <DropdownItem onClick={this.inputFavoriteCity(item)}>{item}</DropdownItem>);
		
        return (
            <Router>
                <div className={`main bg-faded ${this.state.group}`}>
                    <div className='container'>
                        <Navbar color="faded" light expand="md">
                            <NavbarBrand className='text-info' href="/">WeatherMood</NavbarBrand>
                            <NavbarToggler onClick={this.handleNavbarToggle}/>
                            <Collapse isOpen={this.state.navbarToggle} navbar>
                                <Nav navbar>
                                    <NavItem>
                                        <NavLink tag={Link} to='/'>Today</NavLink>
                                    </NavItem>
                                    <NavItem>
                                        <NavLink tag={Link} to='/forecast'>Forecast</NavLink>
                                    </NavItem>
                                    <UncontrolledDropdown>
                                        <DropdownToggle nav caret>
                                            Favorite City
                                        </DropdownToggle>
                                        <DropdownMenu right>
                                           	{cities}
											<DropdownItem divider />
                                            <DropdownItem onClick={this.clearFavoriteCities}>
                                                Clear
                                            </DropdownItem>
                                        </DropdownMenu>
                                    </UncontrolledDropdown>
                                </Nav>
                                <span className='navbar-text ml-auto'>DataLab</span>
                            </Collapse>
                        </Navbar>
                    </div>

                    <Route exact path="/" render={() => (
                        <Today city={this.state.city} unit={this.state.unit} onQuery={this.handleFormQuery} />
                    )}/>
                    <Route exact path="/forecast" render={() => (
                        <Forecast unit={this.state.unit} onUnitChange={this.handleUnitChange} />
                    )}/>
                </div>
            </Router>
        );
    }
    // TODO
    setFavoriteCities(city) {
    	const { cookies } = this.props;
		var cities = this.state.favoriteCities;
		cities.push(city)
		cookies.set('cities', cities.join(';'), { path: '/' } );	
		this.setState({
			favoriteCities: cities
		});
	}

    handleNavbarToggle() {
        this.setState((prevState, props) => ({
            navbarToggle: !prevState.navbarToggle
        }));
    }
    // TODO
    handleFormQuery(city, unit) {
        this.setState({
            city: city,
            unit: unit
        }, ()=>{
			this.setFavoriteCities(city)
		});
    }
    // TODO
    clearFavoriteCities() {
		const { cookies } = this.props;
    	cookies.set('cities', '');
		this.setState({
			favoriteCities: []
		});
	}

	inputFavoriteCity(name) {
		return (() => {
			console.log(this)
			this.setState({
				city: name
			});
		}).bind(this)
	}
}

export default withCookies(Main);
