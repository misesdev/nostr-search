'use client';

import { ReactNode } from 'react';

export default function CountryLookup(): ReactNode {
    const country = 'United States';

    // useEffect(() => {
    //     const getCountry = async () => {
    //         const response = await fetch(
    //             `https://extreme-ip-lookup.com/json/?key=${process.env.NEXT_PUBLIC_IP_API_KEY}`
    //         )
    //             .then((res) => res.json())
    //             .then((data) => data.country);
    //         if (!response) return;
    //         setCountry(response);
    //     };
    //     getCountry();
    // }, []);

    return <div className="text-gray-300">{country}</div>;
}
